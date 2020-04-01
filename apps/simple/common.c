#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>

#include "xdcomms.h"
#include "gma.h"
#include "common.h"

#define DIR_SEND   0
#define DIR_RECV   1
#define NUM_DIRS   2

#define TYPE_DIS   0
#define TYPE_POS   1
#define TYPE_TOTAL 2
#define NUM_TYPES  3

typedef struct _stats {
    int delay;
    int count;
    int time;
    int last_count;
} stats_type;

stats_type stats[NUM_DIRS][NUM_TYPES];

int delay_in_ms_dis = 10;
int delay_in_ms_pos = 100;

int recv_count_pos = 0;
int recv_count_dis = 0;

int send_count_pos = 0;
int send_count_dis = 0;

int send_count_total = 0;
int recv_count_total = 0;

int elapse_seconds = 0;

pthread_mutex_t recv_lock;
pthread_mutex_t send_lock;

int display_interval = 10;         // in seconds

char benchmarking = 0;

char ipc_pub[MAX_IPC_LEN];
char ipc_sub[MAX_IPC_LEN];


static int last_send_dis;
static int last_send_pos;
static int last_recv_dis;
static int last_recv_pos;

void stats_line(int send, int position, int total_count, int last_count)
{
    char *dir = send ? "send" : "recv";
    char *type = position ? "position" : "distance";

    printf("%s %s | %7d %8.2f Hz | %7d %8.2f Hz\n",
            dir, type,
            (total_count - last_count),
            (total_count - last_count) / (double) display_interval,
            total_count,
            total_count / (double) elapse_seconds);
}

void show_stats()
{
    printf("elapsed time: %ds, display interval: %ds\n", elapse_seconds, display_interval);

    stats_line(1, 0, send_count_dis, last_send_dis);
    stats_line(1, 1, send_count_pos, last_send_pos);
    stats_line(0, 0, recv_count_dis, last_recv_dis);
    stats_line(0, 1, recv_count_pos, last_recv_pos);

    printf("\n");

    last_send_dis = send_count_dis;
    last_send_pos = send_count_pos;
    last_recv_dis = recv_count_dis;
    last_recv_pos = recv_count_pos;
}

void *benchmark()
{
    printf("creating benchmark thread\n");

    while (1) {
        sleep(1);
        elapse_seconds++;

        if (benchmarking && (elapse_seconds % display_interval == 0)) {
            show_stats();
        }
    }

    return NULL;
}

void sig_handler(int signo)
{
    printf("%d %d\n", signo, SIGINT);
    if (signo == SIGINT) {
        show_stats();
        exit(0);
    }
}

void init_locks()
{
    signal(SIGINT, sig_handler);

    recv_count_pos = 0;

    if (pthread_mutex_init(&recv_lock, NULL) != 0)
    {
        printf("\n mutex recv init failed\n");
        exit(1);
    }

    if (pthread_mutex_init(&send_lock, NULL) != 0)
    {
        printf("\n mutex send init failed\n");
        exit(1);
    }
}

void usage()
{
    printf("Usage: <this-program> \n\
\t -h     \t help\n\
\t -b     \t benchmark mode\n\
\t -d <Hz>\t Distance Hertz (default 100 Hz)\n\
\t -p <Hz>\t Position Hertz (default 10 Hz)\n\
\t -i <sub>\t Subscribe endpoint\n\
\t -o <pub>\t Publish endpoint\n\
\t -v <period>\t Interval in seconds to display statistics in benchmarking (default 10s)\n");
    exit(1);
}

int get_hertz(char *arg)
{
    int hertz = atoi(arg);
    if (hertz <= 0) {
        printf("bad argument %s\n", arg);
        usage();
    }
    return (int) (1000 / (double) hertz);
}

void parse(int argc, char **argv)
{
    int c;
    while ((c = getopt(argc, argv, "hbd:p:v:i:o:")) != -1) {
        switch (c) {
        case 'b':
            benchmarking = 1;
            break;
        case 'd':
            delay_in_ms_dis = get_hertz(optarg);
            break;
        case 'p':
            delay_in_ms_pos = get_hertz(optarg);
            break;
        case 'v':
            display_interval = atoi(optarg);
            break;
        case 'i':
            strcpy(ipc_sub, optarg);
            break;
        case 'o':
            strcpy(ipc_pub, optarg);
            break;
        case 'h':
            usage();
            break;
        default:
            usage();
        }
    }
}

void *init_hal()
{
    void *ctx = xdc_ctx();

    xdc_set_out(ipc_pub);
    xdc_set_in(ipc_sub);

    xdc_register(position_data_encode, position_data_decode, DATA_TYP_POSITION);
    xdc_register(distance_data_encode, distance_data_decode, DATA_TYP_DISTANCE);

    return ctx;
}

void *recv_distance(uint32_t t_mux, uint32_t t_sec, uint32_t type, int port)
{
    pong_sender(port);

    gaps_tag t_tag;

    tag_write(&t_tag, t_mux, t_sec, type);
    void *socket = xdc_sub_socket(t_tag);

    distance_datatype dis;

    recv_count_dis = 0;
    while (1) {
        xdc_blocking_recv(socket, &dis, &t_tag);

        pthread_mutex_lock(&recv_lock);
        recv_count_total++;
        pthread_mutex_unlock(&recv_lock);

        recv_count_dis++;

        if (!benchmarking) {
            printf("\t\t\t\t\t\trecv distance %6d: (%6.0f, %6.0f, %6.0f)\n", recv_count_dis, dis.x, dis.y, dis.z);
        }
    }
    zmq_close(socket);

    return NULL;
}

void *recv_position(uint32_t t_mux, uint32_t t_sec, uint32_t type, int port)
{
    pong_sender(port);

    gaps_tag t_tag;
    tag_write(&t_tag, t_mux, t_sec, type);

    void *socket = xdc_sub_socket(t_tag);

    position_datatype pos;

    recv_count_pos = 0;
    while (1) {
        xdc_blocking_recv(socket, &pos, &t_tag);

        pthread_mutex_lock(&recv_lock);
        recv_count_total++;
        pthread_mutex_unlock(&recv_lock);

        recv_count_pos++;

        if (!benchmarking) {
            printf("\t\t\t\t\t\trecv position %6d: (%6.0f, %6.0f, %6.0f)\n", recv_count_pos, pos.x, pos.y, pos.z);
        }
    }
    zmq_close(socket);

    return NULL;
}

void *send_position(uint32_t t_mux, uint32_t t_sec, uint32_t type, int port)
{
    ping_receiver(port);

    position_datatype pos;
    pos.x = 1;
    pos.y = 1;
    pos.z = 1;

    void *send_pos_socket = xdc_pub_socket();

    send_count_pos = 0;
    while (1) {
        usleep(delay_in_ms_pos * 1000);

        pos.trailer.seq = 1;
        pos.trailer.rqr = 1;
        pos.trailer.oid = 1;
        pos.trailer.mid = 1;
        pos.trailer.crc = 1;

        gaps_tag  t_tag;

        tag_write(&t_tag, t_mux, t_sec, type);

        xdc_asyn_send(send_pos_socket, &pos, t_tag);

        pthread_mutex_lock(&send_lock);
        send_count_total++;
        pthread_mutex_unlock(&send_lock);

        send_count_pos++;

        if (!benchmarking) {
            printf("sent position %6d: (%6.0f, %6.0f, %6.0f)\n", send_count_pos, pos.x, pos.y, pos.z);
        }

        pos.x += 2;
        pos.y += 2;
        pos.z += 2;
    }
    zmq_close(send_pos_socket);

    return NULL;
}

void *send_distance(uint32_t t_mux, uint32_t t_sec, uint32_t type, int port)
{
    ping_receiver(port);

    distance_datatype dis;
    dis.x = 1;
    dis.y = 1;
    dis.z = 1;

    void *send_dis_socket = xdc_pub_socket();

    send_count_dis = 0;
    while (1) {
        usleep(delay_in_ms_dis * 1000);

        dis.trailer.seq = 1;
        dis.trailer.rqr = 1;
        dis.trailer.oid = 1;
        dis.trailer.mid = 1;
        dis.trailer.crc = 1;

        gaps_tag  t_tag;

        tag_write(&t_tag, t_mux, t_sec, type);

        xdc_asyn_send(send_dis_socket, &dis, t_tag);

        pthread_mutex_lock(&send_lock);
        send_count_total++;
        pthread_mutex_unlock(&send_lock);

        send_count_dis++;

        if (!benchmarking) {
            printf("sent distance %6d: (%6.0f, %6.0f, %6.0f)\n", send_count_dis, dis.x, dis.y, dis.z);
        }

        dis.x += 2;
        dis.y += 2;
        dis.z += 2;
    }
    zmq_close(send_dis_socket);

    return NULL;
}

void pong_sender(int port)
{
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
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    printf("ponging sender at port %d.\n", port);

    struct sockaddr_in cliaddr;
    memset(&cliaddr, 0, sizeof(cliaddr));
    int len = sizeof(cliaddr);

    int n = recvfrom(sockfd, (char *) buffer, BUF_SIZE, 0,
                    (struct sockaddr *) &cliaddr, (unsigned int *) &len);
    if (n < 0) {
        perror("failed to receive");
        exit(EXIT_FAILURE);
    }

    const char *rsp = "pong";
    sendto(sockfd, rsp, strlen(rsp), 0, (const struct sockaddr *) &cliaddr, len);
}

void ping_receiver(int port)
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

    printf("pinging receiver at port %d.\n", port);

    int len;
    strcpy(buffer, "ping");
    while (1) {
        sendto(sockfd, (const char *) buffer, strlen(buffer), 0,
               (const struct sockaddr *) &recv, sizeof(recv));

        int n = recvfrom(sockfd, (char *)buffer, BUF_SIZE, 0,
                         (struct sockaddr *) &recv, (unsigned int *) &len);
        if (n > 0) {
            printf("receiver at port %d is up\n", port);
            return;
        }
    }
    close(sockfd);
}
