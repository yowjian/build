#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
#include <errno.h>
#include <ctype.h>

#include "xdcomms.h"
#include "gma.h"
#include "common.h"
#include "utils.h"

stats_type stats[NUM_DIRS][NUM_TYPES];

pthread_mutex_t recv_lock;
pthread_mutex_t send_lock;

char verbose = 0;

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

void set_total_done(stats_type *nums)
{
    pthread_mutex_lock(&recv_lock);

    nums->done = 1;

    if (stats[DIR_RECV][TYPE_DIS].done && stats[DIR_RECV][TYPE_DIS].sender_count > 0 &&
        stats[DIR_RECV][TYPE_POS].done && stats[DIR_RECV][TYPE_POS].sender_count > 0)
        stats[DIR_RECV][TYPE_TOTAL].done = 1;

    pthread_mutex_unlock(&recv_lock);
}

void *waiting(void *args)
{
    stats_type *nums = (stats_type *) args;

    while (1) {
        int old_sender_count = nums->sender_count;
        nums->sender_count = update_from_sender(nums->sock);

        pthread_mutex_lock(&recv_lock);
        stats[DIR_RECV][TYPE_TOTAL].sender_count -= old_sender_count;
        stats[DIR_RECV][TYPE_TOTAL].sender_count += nums->sender_count;
        pthread_mutex_unlock(&recv_lock);

        if (nums->expected > 0 && nums->sender_count >= nums->expected) {
            set_total_done(nums);
            break;
        }
    }

    sleep(10);  // let the packets in flight be received.
    pthread_cancel(nums->thread);

    return NULL;
}

void wait_for_completion(stats_type *nums)
{
    pthread_t waitThread;
    int rtn = pthread_create(&waitThread, NULL, &waiting, nums);
    if (rtn != 0) {
        printf("receice thread creat failed\n");
        exit(1);
    }
}

void *gaps_read(uint32_t t_mux, uint32_t t_sec, uint32_t type, int port)
{
    int type_idx = (type == DATA_TYP_POSITION) ? TYPE_POS : TYPE_DIS;
    stats_type *nums = &stats[DIR_RECV][type_idx];

    nums->port = port;

    gaps_tag t_tag;

    tag_write(&t_tag, t_mux, t_sec, type);
    void *socket = xdc_sub_socket(t_tag);

    char pkt[MAX_PKT_LEN];

    init_time(nums);
    init_time(&stats[DIR_RECV][TYPE_TOTAL]);

    // notify the sender that this is ready to receive
    nums->sock = pong_sender(port, &nums->expected);
    pthread_mutex_lock(&recv_lock);
    stats[DIR_RECV][TYPE_TOTAL].expected += nums->expected;
    pthread_mutex_unlock(&recv_lock);

    // another thread to wait for send completion to cancel this thread
    nums->thread = pthread_self();
    wait_for_completion(nums);
    while (1) {
        xdc_blocking_recv(socket, pkt, &t_tag);

        pthread_mutex_lock(&recv_lock);
        stats[DIR_RECV][TYPE_TOTAL].count++;
        pthread_mutex_unlock(&recv_lock);

        nums->count++;

        if (type == DATA_TYP_POSITION) {
            position_datatype *pos = (position_datatype *) pkt;
            cal_char(nums, &pos->trailer);
            if (verbose)
                printf("\t\t\t\t\t\trecv position %6d: (%6.0f, %6.0f, %6.0f)\n", nums->count, pos->x, pos->y, pos->z);
        }
        else {
            distance_datatype *dis = (distance_datatype *) pkt;
            cal_char(nums, &dis->trailer);
            if (verbose)
                printf("\t\t\t\t\t\trecv distance %6d: (%6.0f, %6.0f, %6.0f)\n", nums->count, dis->x, dis->y, dis->z);
        }
    }
    zmq_close(socket);

    return NULL;
}

void *gaps_write(uint32_t t_mux, uint32_t t_sec, uint32_t type, int port)
{
    int type_idx = (type == DATA_TYP_POSITION) ? TYPE_POS : TYPE_DIS;
    stats_type *nums = &stats[DIR_SEND][type_idx];

    char *type_str = (type == DATA_TYP_POSITION) ? "positions" : "distance";

    if (nums->interval < 0) {
        printf("interval = %lli, not sending %s\n", nums->interval, type_str);
        return NULL;
    }

    gaps_tag  t_tag;
    tag_write(&t_tag, t_mux, t_sec, type);

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

    init_time(nums);
    init_time(&stats[DIR_SEND][TYPE_TOTAL]);

    unsigned long long curr = get_time();
    int sock = ping_receiver(port, nums->expected);
    while (1) {
        usleep(nums->interval);

        pos.trailer.seq = pos.x;
        encode_timestamp(&pos.trailer);
        xdc_asyn_send(send_socket, &pos, t_tag);

        pthread_mutex_lock(&send_lock);
        stats[DIR_SEND][TYPE_TOTAL].count++;
        pthread_mutex_unlock(&send_lock);

        nums->count++;

        if (verbose) {
            printf("sent %s %6d: (%6.0f, %6.0f, %6.0f)\n", type_str, nums->count, pos.x, pos.y, pos.z);
        }

        pos.x++;
        pos.y++;
        pos.z++;

        if (get_time() - curr > 1000) {
            update_receiver(sock, port, nums->count);
            curr = get_time();
        }

        if (nums->expected > 0 && nums->count >= nums->expected) {
            close_time(nums);
            break;
        }
    }
    zmq_close(send_socket);

    update_receiver(sock, port, nums->expected);

    return NULL;
}

int pong_sender(int port, int *to_recv)
{
    // printf("pong_sender at port %d.\n", port);

    const int BUF_SIZE = 64;
    int sockfd;
    char buffer[BUF_SIZE];
    struct sockaddr_in servaddr;

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(port);
    if (bind(sockfd, (const struct sockaddr *) &servaddr, sizeof(servaddr)) < 0) {
        perror("pong_sender: bind failed");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in cliaddr;
    memset(&cliaddr, 0, sizeof(cliaddr));
    int len = sizeof(cliaddr);

    int n = recvfrom(sockfd, (char *) buffer, BUF_SIZE, 0,
                    (struct sockaddr *) &cliaddr, (unsigned int *) &len);
    if (n < 0 || n >= BUF_SIZE) {
        perror("failed to receive");
        exit(EXIT_FAILURE);
    }
    buffer[n] = '\0';

    *to_recv = atoi(buffer);

    const char *rsp = "pong";
    sendto(sockfd, rsp, strlen(rsp), 0, (const struct sockaddr *) &cliaddr, len);

    return sockfd;
}

int ping_receiver(int port, int to_send)
{
    const int BUF_SIZE = 64;
    int sockfd;
    char buffer[BUF_SIZE];
    struct sockaddr_in recv;

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    struct timeval tv;
    tv.tv_sec = 1;
    tv.tv_usec = 0;
    if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO,&tv,sizeof(tv)) < 0) {
        perror("Error");
    }

    memset(&recv, 0, sizeof(recv));
    recv.sin_family = AF_INET;
    recv.sin_port = htons(port);
    recv.sin_addr.s_addr = INADDR_ANY;

    // printf("pinging receiver at port %d.\n", port);

    char msg[BUF_SIZE];
    sprintf(msg, "%d", to_send);

    int len;
    while (1) {
        sendto(sockfd, (const char *) msg, strlen(msg), 0,
               (const struct sockaddr *) &recv, sizeof(recv));

        int n = recvfrom(sockfd, (char *)buffer, BUF_SIZE, 0,
                         (struct sockaddr *) &recv, (unsigned int *) &len);
        if (n > 0) {
            // printf("receiver at port %d is up\n", port);
            return sockfd;
        }
    }
    return -1;
}

void update_receiver(int sock, int port, int count)
{
    const int BUF_SIZE = 16;

    char msg[BUF_SIZE];
    sprintf(msg, "%d", count);

    struct sockaddr_in recv;
    memset(&recv, 0, sizeof(recv));
    recv.sin_family = AF_INET;
    recv.sin_port = htons(port);
    recv.sin_addr.s_addr = INADDR_ANY;

    int n = sendto(sock, (const char *) msg, strlen(msg), 0,
                   (const struct sockaddr *) &recv, sizeof(recv));
    if (n <= 0) {
        printf("*** failed to update receiver: %s\n", strerror(errno));
    }
}

int update_from_sender(int sock)
{
    const int BUF_SIZE = 16;
    char msg[BUF_SIZE];

    struct sockaddr_in recv;
    memset(&recv, 0, sizeof(recv));

    int len;
    int n = recvfrom(sock, (char *)msg, BUF_SIZE, 0,
                     (struct sockaddr *) &recv, (unsigned int *) &len);
    if (n <= 0) {
        printf("failed to receiver update from sender");
        return -1;
    }
    msg[n] = '\0';

    return get_int(msg);
}
