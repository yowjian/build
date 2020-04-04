#pragma once

#define MAX_IPC_LEN     128
#define MAX_PKT_LEN     4096

typedef enum _flow_state_t {
    INIT,
    READY,
    STARTED,
    DONE,
    TERMINATED
} flow_state_t;

typedef struct _characteristics_t {
    double max;
    double min;
    double avg;
    double last;
    int count;
    int last_seq;
    char first;
} characteristics_t;

typedef struct _stats {
    long long interval;
    int expected;                   // number of pkts expected to send or receive
    int count;                      // current count of sent or received pkts
    int sender_count;               // sender's count received out of band
    int last_count;                 // count of sent or received pkts in the last period
    unsigned long long time;        // current time in ms
    unsigned long long last_time;   // time of the last period in ms
    unsigned long long start_time;  // start time of the thread in ms
    pthread_t thread;               // thread associated with this flow

    characteristics_t delay;
    characteristics_t jitter;
    characteristics_t loss;
} stats_type;

typedef struct _flow_t {
    int id;
    int rate;
    int mux;
    int sec;
    int type;
    flow_state_t state;
    unsigned long long last_update;     // last time the receiver was updated with sent count
    sem_t sem;                          // wait until the receiver is ready before sending
    stats_type stats;
    struct _enclave_t *dst;

    struct _flow_t *next;
} flow_t;

typedef struct _enclave_t {
    char name[16];
    char pub[64];      // IPC publication
    char sub[64];      // IPC subscription
    int port;          // port to send/recv out-of-band data
    flow_t *flows;     // list of flows sent from this enclave
    struct _enclave_t *next;
} enclave_t;

extern enclave_t *my_enclave;
extern char verbose;
extern unsigned long long sys_start_time;
extern int display_interval;
extern enclave_t *all_enclaves;

unsigned long long get_time();
char *center(char *str, int width, char **dst);
long long get_interval(int hz);
int get_int(char *str);
char *trim(char *str);
void *init_hal();
void init_time(stats_type *nums);
void flow_close(flow_t *flow);
void encode_timestamp(trailer_datatype *trailer);
unsigned long long decode_timestamp(trailer_datatype *trailer);
void cal_char(stats_type *nums, trailer_datatype *trailer);
void init_locks();

void show_stats();
void init_stats(int hz_dis, int hz_pos);

void usage();
void parse(int argc, char **argv);

flow_t *find_flow(int id);
enclave_t *find_enclave(char *name);

void die(char *s);
