#pragma once
#include <signal.h>
#include <semaphore.h>

#define MAX_IPC_LEN     128
#define MAX_PKT_LEN     4096

typedef enum _flow_state_t {
    INIT,
    READY,
    STARTED,
    DONE
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
    char done;                      // 1 for complete; 0 otherwise
    int port;                       // UDP port to wait or send out-of-band data
    int sock;                       // socket for out-of-band data
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
    unsigned long long last_update;
    sem_t sem;
    stats_type stats;
    struct _enclave_t *dst;
    struct _flow_t *next;
} flow_t;

typedef struct _enclave_t {
    char enclave[16];
    char pub[64];
    char sub[64];
    char tx;
    int port;
    int count;
    flow_t *flows;
    struct _enclave_t *next;
} enclave_t;

extern enclave_t *my_enclave;
extern char verbose;
extern unsigned long long sys_start_time;

void die(char *s);
void *benchmark();
