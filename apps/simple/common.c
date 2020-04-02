#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>

#include "xdcomms.h"
#include "gma.h"
#include "common.h"

static char *type_names[NUM_TYPES] = { "distance", "posistion", "total" };

stats_type stats[NUM_DIRS][NUM_TYPES];

pthread_mutex_t recv_lock;
pthread_mutex_t send_lock;

int display_interval = 10;         // in seconds

char benchmarking = 0;

char ipc_pub[MAX_IPC_LEN];
char ipc_sub[MAX_IPC_LEN];

unsigned long long get_time()
{
    struct timeval tv;

    gettimeofday(&tv, NULL);

    return  (unsigned long long)(tv.tv_sec) * 1000 +
            (unsigned long long)(tv.tv_usec) / 1000;
}

void stats_line(int type)
{
    stats_type *nums = &stats[DIR_SEND][type];

    if (!nums->done)
        nums->time = get_time();

    double elapse_seconds = (nums->time - nums->start_time) / 1000;
    double percentage = (nums->to_transfer <= 0) ? 0 : (nums->count * 100.0 / nums->to_transfer);
    double rate = nums->count / (double) elapse_seconds;

    printf("%9s|%5d %7.2f|%7d %8.2f%7.2f",
            type_names[type],
            (nums->count - nums->last_count),
            (nums->count - nums->last_count) / (double) display_interval,
            nums->count,
            rate,
            percentage);

    nums = &stats[DIR_RECV][type];
    if (!nums->done)
        nums->time = get_time();

    elapse_seconds = (nums->time - nums->start_time) / 1000;
    percentage = (nums->to_transfer <= 0) ? 0 : (nums->count * 100.0 / nums->to_transfer);

    printf("|%5d %7.2f|%7d %8.2f%7.2f|\n",
            (nums->count - nums->last_count),
            (nums->count - nums->last_count) / (double) display_interval,
            nums->count,
            nums->count / (double) elapse_seconds,
            percentage);
}

char *center(char *str, int width, char **dst)
{
    int len = strlen(str);

    if (*dst == NULL) {
        char *buf = malloc(width);
        *dst = buf;

        int offset = (width - len) / 2;
        memset(buf, ' ', width - 1);
        strcpy(buf + offset, str);
        buf[offset + len] = ' ';
        buf[width - 1] = '\0';
    }

    return *dst;
}

void show_duration(int dir, int type)
{
    int sec, h, m, s;

    unsigned long long ms = get_time() - stats[dir][type].start_time;

    if (stats[dir][type].start_time == 0)
        ms = 0;

    sec = ms / 1000;
    h = (sec / 3600);
    m = (sec - (3600 * h)) / 60;
    s = (sec - (3600 * h) - (m * 60));

    time_t rawtime;
    struct tm *info;
    char buffer[80];

    time(&rawtime);

    info = localtime(&rawtime);

    strftime(buffer, 80, "%H:%M:%S", info);

    printf("current time: %s, \t elapsed time: %02d:%02d:%02d\n", buffer, h, m, s);
}

void show_stats()
{
    static char *send_ptr = NULL;
    static char *recv_ptr = NULL;
    static char *inst_ptr = NULL;
    static char *accu_ptr = NULL;

    show_duration(DIR_SEND, TYPE_POS);

    center("Send", 38, &send_ptr);
    center("Receive", 38, &recv_ptr);

    center("this period", 14, &inst_ptr);
    center("accumulated", 24, &accu_ptr);

    printf("%9s|%s|%s|\n", " ", send_ptr, recv_ptr);
    printf("%9s|%s|%s|%s|%s|\n", " ", inst_ptr, accu_ptr, inst_ptr, accu_ptr);
    printf("%9s|%6s%7s|%6s%10s%7s|%6s%7s|%6s%10s%7s|\n", " ",
            "count", "rate", "count", "rate", "%",
            "count", "rate", "count", "rate", "%");

    for (int j = 0; j < NUM_TYPES; j++) {
        stats_line(j);
    }

    for (int i = 0; i < NUM_DIRS; i++) {
        for (int j = 0; j < NUM_TYPES; j++) {
            stats_type *nums = &stats[i][j];
            nums->last_count = nums->count;
            nums->last_time = nums->time;
        }
    }
    printf("\n");
}

/**
 * Return delay in us, given hertz.
 */
long long get_delay(int hz)
{
    if (hz == 0)
        return -1;  // not running the sender

    return (long long) (1000000 / (double) hz);
}

int get_int(char *str)
{
    int i = atoi(str);
    if (i < 0) {
        printf("bad argument %s\n", str);
        usage();
        return -1;
    }

    return i;
}

void init_stats(int hz_dis, int hz_pos)
{
    memset((char *)stats, 0, sizeof(stats_type) * NUM_DIRS * NUM_TYPES);

    stats[DIR_SEND][TYPE_DIS].delay = get_delay(hz_dis);
    stats[DIR_SEND][TYPE_DIS].to_transfer = -1; // no limit;

    stats[DIR_SEND][TYPE_POS].delay = get_delay(hz_pos);
    stats[DIR_SEND][TYPE_POS].to_transfer = -1; // no limit
}

void *benchmark()
{
    printf("creating benchmark thread\n");

    int elapse_seconds = 0;
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
\t -x <count>\t Distance send count (default unlimited)\n\
\t -y <count>\t Position send count (default unlimited)\n\
\t -i <sub>\t Subscribe endpoint\n\
\t -o <pub>\t Publish endpoint\n\
\t -v <period>\t Interval in seconds to display statistics in benchmarking (default 10s)\n");
    exit(1);
}

void parse(int argc, char **argv)
{
    int c;
    while ((c = getopt(argc, argv, "hbd:p:v:i:o:x:y:")) != -1) {
        switch (c) {
        case 'b':
            benchmarking = 1;
            break;
        case 'd':
            stats[DIR_SEND][TYPE_DIS].delay = get_delay(get_int(optarg));
            break;
        case 'p':
            stats[DIR_SEND][TYPE_POS].delay = get_delay(get_int(optarg));
            break;
        case 'x':
            stats[DIR_SEND][TYPE_DIS].to_transfer = get_int(optarg);
            break;
        case 'y':
            stats[DIR_SEND][TYPE_POS].to_transfer = get_int(optarg);
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

void init_time(stats_type *nums)
{
    if (nums->start_time != 0)
        return;

    nums->time = get_time();
    nums->last_time = nums->time;
    nums->start_time = nums->time;
}

void close_time(stats_type *nums)
{
    nums->done = 1;
    nums->time = get_time();
}

void *waiting(void *args)
{
    stats_type *nums = (stats_type *) args;

    pong_sender(nums->port, &nums->to_transfer);
    nums->done = 1;

    return NULL;
}

void wait_for_completion(stats_type *stats)
{
    pthread_t waitThread;
    int rtn = pthread_create(&waitThread, NULL, &waiting, stats);
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

    pong_sender(port, &nums->to_transfer); // notify the sender that this is ready to receive
    wait_for_completion(nums);  // another thread to wait for completion, setting done to 1
    while (!nums->done) {
        xdc_blocking_recv(socket, pkt, &t_tag);

        pthread_mutex_lock(&recv_lock);
        stats[DIR_RECV][TYPE_TOTAL].count++;
        pthread_mutex_unlock(&recv_lock);

        nums->count++;

        if (!benchmarking) {
            if (type == DATA_TYP_POSITION) {
                position_datatype *pos = (position_datatype *) pkt;
                printf("\t\t\t\t\t\trecv position %6d: (%6.0f, %6.0f, %6.0f)\n", nums->count, pos->x, pos->y, pos->z);
            }
            else {
                distance_datatype *dis = (distance_datatype *) pkt;
                printf("\t\t\t\t\t\trecv distance %6d: (%6.0f, %6.0f, %6.0f)\n", nums->count, dis->x, dis->y, dis->z);
            }
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

    if (nums->delay < 0) {
        printf("delay = %lli, not sending %s\n", nums->delay, type_str);
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

    ping_receiver(port, nums->to_transfer);
    while (1) {
        usleep(nums->delay);

        xdc_asyn_send(send_socket, &pos, t_tag);

        pthread_mutex_lock(&send_lock);
        stats[DIR_SEND][TYPE_TOTAL].count++;
        pthread_mutex_unlock(&send_lock);

        nums->count++;

        if (!benchmarking) {
            printf("sent %s %6d: (%6.0f, %6.0f, %6.0f)\n", type_str, nums->count, pos.x, pos.y, pos.z);
        }

        pos.x++;
        pos.y++;
        pos.z++;

        if (nums->to_transfer > 0 && nums->count >= nums->to_transfer) {
            close_time(nums);
            break;
        }
    }
    zmq_close(send_socket);

    ping_receiver(port, 0);

    return NULL;
}

void pong_sender(int port, int *to_recv)
{
    printf("pong_sender at port %d.\n", port);

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

    close(sockfd);
}

void ping_receiver(int port, int to_send)
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

    char msg[BUF_SIZE];
    sprintf(msg, "%d", to_send);

    int len;
    while (1) {
        sendto(sockfd, (const char *) msg, strlen(msg), 0,
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
