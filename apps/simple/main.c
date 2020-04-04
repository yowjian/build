#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
#include <errno.h>
#include <ctype.h>
#include <semaphore.h>

#include "xdcomms.h"
#include "gma.h"
#include "main.h"
#include "utils.h"

flow_head_t *my_enclave;

char verbose = 0;
unsigned long long sys_start_time;

void *benchmark()
{
    // printf("creating benchmark thread\n");

    int elapse_seconds = 0;
    while (1) {
        sleep(1);
        elapse_seconds++;

        if (elapse_seconds % display_interval == 0) {
            show_stats();
        }
    }

    return NULL;
}

void *gaps_read(void *args)
{
    flow_t *flow = (flow_t *) args;

    gaps_tag t_tag;
    tag_write(&t_tag, flow->mux, flow->sec, flow->type);

    char pkt[MAX_PKT_LEN];

    stats_type *nums = &flow->stats;

    init_time(nums);
    // init_time(&stats[DIR_RECV][TYPE_TOTAL]);  TODO

    void *socket = xdc_sub_socket(t_tag);

    flow->stats.thread = pthread_self();
    flow->state = READY;

    while (1) {
        xdc_blocking_recv(socket, pkt, &t_tag);
        nums->count++;
        flow->state = STARTED;

        position_datatype *pos = (position_datatype *) pkt;
        cal_char(nums, &pos->trailer);
        if (verbose)
            printf("\t\t\t\t\t\trecv flow %3d, %6d: (%6.0f, %6.0f, %6.0f)\n", flow->id, nums->count, pos->x, pos->y, pos->z);
    }
    zmq_close(socket);

    return NULL;
}

void *gaps_write(void *args)
{
    flow_t *flow = (flow_t *) args;

    gaps_tag  t_tag;
    tag_write(&t_tag, flow->mux, flow->sec, flow->type);

    // position and distance happen to be the same, use position for now
    position_datatype pos;
    pos.x = 1;
    pos.y = 1;
    pos.z = 1;
    pos.trailer.seq = 1;
    pos.trailer.rqr = 1;
    pos.trailer.oid = 1;
    pos.trailer.mid = 1;
    pos.trailer.crc = 1;

    void *send_socket = xdc_pub_socket();

    stats_type *nums = &flow->stats;

    init_time(nums);
    // init_time(&stats[DIR_SEND][TYPE_TOTAL]);

    unsigned long long curr = get_time();

    sem_wait(&flow->sem);
    while (1) {
        usleep(nums->interval);

        pos.trailer.seq = pos.x;
        encode_timestamp(&pos.trailer);

        xdc_asyn_send(send_socket, &pos, t_tag);

        nums->count++;

        if (verbose) {
            printf("sent flow %3d, %6d: (%6.0f, %6.0f, %6.0f)\n", flow->id, nums->count, pos.x, pos.y, pos.z);
        }

        pos.x++;
        pos.y++;
        pos.z++;

        if (get_time() - curr > 1000) {
            curr = get_time();
        }

        if (nums->expected > 0 && nums->count >= nums->expected) {
            close_time(nums);
            break;
        }
    }
    zmq_close(send_socket);

    return NULL;
}

flow_t *find_flow(int id)
{
    flow_head_t *head = flow_heads;

    while (head != NULL) {
        flow_t *flow = head->flows;

        while (flow != NULL) {
            if (flow->id == id)
                return flow;

            flow = flow->next;
        }
        head = head->next;
    }
    return NULL;
}

void *oob_recv(void *args)
{
    const int BUF_SIZE = 64;
    int sockfd;
    struct sockaddr_in recv;

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        die("socket creation failed");
    }

    memset(&recv, 0, sizeof(recv));
    recv.sin_family = AF_INET;
    recv.sin_port = htons(my_enclave->port);
    recv.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (const struct sockaddr *) &recv, sizeof(recv)) < 0) {
        die("bind failed");
    }

    char msg[BUF_SIZE];
    int len;

    if (verbose)
        printf("oob_recv started at port %d.\n", my_enclave->port);

    while (1) {
        int n = recvfrom(sockfd, (char *)msg, BUF_SIZE, 0,
                         (struct sockaddr *) &recv, (unsigned int *) &len);
        if (n <= 0) {
            printf("failed to receiver update from sender");
            continue;
        }
        msg[n] = '\0';

        if (verbose)
            printf("recv %s\n", msg);

        const char *ready = "ready";
        if (!strncmp(msg, ready, strlen(ready))) {
            int id = get_int(trim(msg + strlen(ready) + 1));
            flow_t *flow = find_flow(id);
            if (flow != NULL) {
                sem_post(&flow->sem);  // signal sender to start
            }
        }

        const char *sent = "sent";
        if (!strncmp(msg, sent, strlen(sent))) {
            int id, expected;
            sscanf(msg + strlen(sent) + 1, "%d %d", &id, &expected);
            flow_t *flow = find_flow(id);
            if (flow != NULL) {
                flow->stats.sender_count = expected;
            }
        }
    }
    return NULL;
}

static void oob_send_pkt(char *msg, int sock, struct sockaddr_in *recv)
{
    sendto(sock, (const char *) msg, strlen(msg), 0,
            (const struct sockaddr *) recv, sizeof(*recv));

    if (verbose)
        printf("sent %s\n", msg);
}

void *oob_send(void *args)
{
    const int BUF_SIZE = 64;
    int sockfd;
    struct sockaddr_in recv;

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&recv, 0, sizeof(recv));
    recv.sin_family = AF_INET;
    recv.sin_addr.s_addr = INADDR_ANY;

    char msg[BUF_SIZE];

    if (verbose)
        printf("oob_send started.\n");

    while (1) {
        flow_t *flow = my_enclave->flows;
        unsigned long long curr = get_time();

        while (flow != NULL) {
            recv.sin_port = htons(flow->dst->port);

            if (flow->stats.count > 0 && flow->stats.expected >= flow->stats.count) {
                if (flow->state != DONE) {
                    sprintf(msg, "end %d", flow->id);
                    oob_send_pkt(msg, sockfd, &recv);

                    flow->state = DONE;
                }
            }
            else if (curr - flow->last_update > 1000) {
                sprintf(msg, "sent %d %d", flow->id, flow->stats.count);
                oob_send_pkt(msg, sockfd, &recv);

                flow->last_update = curr;
            }
            flow = flow->next;
        }

        flow_head_t *head = flow_heads;
        while (head != NULL) {
            if (head != my_enclave) {
                recv.sin_port = htons(head->port);

                flow_t *flow = head->flows;
                while (flow != NULL) {
                    if (flow->state == READY) {
                        sprintf(msg, "ready %d", flow->id);
                        oob_send_pkt(msg, sockfd, &recv);
                    }
                    else if (flow->stats.expected >= flow->stats.count) {
                        flow->state = DONE;
                    }
                    flow = flow->next;
                }
            }
            head = head->next;
        }
        sleep(1);
    }
    return NULL;
}

static void start_all_threads()
{
    flow_head_t *head = flow_heads;
    while (head != NULL) {
        flow_t *flow = head->flows;
        while (flow != NULL) {
            printf("flow %d: %d %d %d %d\n", flow->id, flow->rate, flow->mux, flow->sec, flow->type);

            pthread_t thread;
            int rtn = pthread_create(&thread, NULL, head->tx ? &gaps_write : &gaps_read, flow);
            if (rtn != 0) {
                die("thread create failed\n");
            }
            flow = flow->next;
        }
        head = head->next;
    }

    pthread_t thread;
    int rtn = pthread_create(&thread, NULL, &oob_recv, my_enclave);
    if (rtn != 0) {
        die("thread create failed\n");
    }

    rtn = pthread_create(&thread, NULL, &oob_send, flow_heads);
    if (rtn != 0) {
        die("thread create failed\n");
    }

    pthread_t benchmarkThread;
    rtn = pthread_create(&benchmarkThread, NULL, &benchmark, NULL);
    if (rtn != 0) {
        die("benchmark thread creat failed\n");
    }
}

static void sig_handler(int signo)
{
    printf("%d %d\n", signo, SIGINT);
    if (signo == SIGINT) {
        show_stats();
        exit(0);
    }
}

int main(int argc, char **argv)
{
    // defaults
    strcpy(ipc_pub, "ipc:///tmp/halpubbworange");
    strcpy(ipc_sub, "ipc:///tmp/halsubbworange");

    parse(argc, argv);

    signal(SIGINT, sig_handler);
    init_hal();

    sys_start_time = get_time();

    start_all_threads();

    pthread_exit(NULL);
}
