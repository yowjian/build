#pragma once

extern int delay_in_ms_dis;
extern int delay_in_ms_pos;

extern int recv_count_pos;
extern int recv_count_dis;

extern int send_count_pos;
extern int send_count_dis;

extern int elapse_seconds;

extern pthread_mutex_t recv_lock;
extern pthread_mutex_t send_lock;

extern char benchmarking;

void *benchmark();
void init_locks();
void usage();
int get_hertz(char *arg);
void parse(int argc, char **argv);
void *init_hal(char *out, char *in);
void *recv_position(uint32_t t_mux, uint32_t t_sec, uint32_t type);
void *recv_distance(uint32_t t_mux, uint32_t t_sec, uint32_t type);
void *send_position(uint32_t t_mux, uint32_t t_sec, uint32_t type);
void *send_distance(uint32_t t_mux, uint32_t t_sec, uint32_t type);
