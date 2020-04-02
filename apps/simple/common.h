#pragma once
#include <signal.h>

#define MAX_IPC_LEN     64
#define MAX_PKT_LEN     2048

#define PORT_ORANGE_TO_GREEN_DIS  9001
#define PORT_ORANGE_TO_GREEN_POS  9003

#define PORT_GREEN_TO_ORANGE_DIS  9002
#define PORT_GREEN_TO_ORANGE_POS  9004

#define DIR_SEND   0
#define DIR_RECV   1
#define NUM_DIRS   2

#define TYPE_DIS   0
#define TYPE_POS   1
#define TYPE_TOTAL 2
#define NUM_TYPES  3

typedef struct _stats {
    long long delay;
    int to_transfer;
    int count;
    int last_count;
    unsigned long long time;
    unsigned long long last_time;
    unsigned long long start_time;
    char done;
} stats_type;

extern stats_type stats[][NUM_TYPES];

extern pthread_mutex_t recv_lock;
extern pthread_mutex_t send_lock;

extern char benchmarking;
extern char ipc_pub[];
extern char ipc_sub[];

void *benchmark();
void init_locks();
void usage();
void parse(int argc, char **argv);
void *init_hal();
void *gaps_write(uint32_t t_mux, uint32_t t_sec, uint32_t type, int port);
void *gaps_read(uint32_t t_mux, uint32_t t_sec, uint32_t type, int port);
void pong_sender(int port, int *to_recv);
void ping_receiver(int port, int to_send);
void sig_handler(int signo);
void init_stats(int delay_dis, int delay_pos);
