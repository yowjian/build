#pragma once
#include <signal.h>

#define MAX_IPC_LEN     64

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
    int delay;
    int count;
    int last_count;
    unsigned long long time;
    unsigned long long last_time;
    unsigned long long start_time;
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
int get_hertz(char *arg);
void parse(int argc, char **argv);
void *init_hal();
void *recv_position(uint32_t t_mux, uint32_t t_sec, uint32_t type, int port);
void *recv_distance(uint32_t t_mux, uint32_t t_sec, uint32_t type, int port);
void *send_position(uint32_t t_mux, uint32_t t_sec, uint32_t type, int port);
void *send_distance(uint32_t t_mux, uint32_t t_sec, uint32_t type, int port);
void pong_sender(int port);
void ping_receiver(int port);
void sig_handler(int signo);
void init_stats(int delay_dis, int delay_pos);
