#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#include "xdcomms.h"
#include "gma.h"
#include "common.h"

void *send_socket = NULL;
int delay_in_ms = 10;

void *green_send_position(void *args)
{
    return send_position(1, 1, DATA_TYP_POSITION);
}

void *green_recv_distance()
{
    return recv_distance(2, 2, DATA_TYP_DISTANCE);
}

void *green_recv_position()
{
    return recv_position(2, 2, DATA_TYP_POSITION);
}

int main(int argc, char **argv)
{
    delay_in_ms_dis = 10000000;
    delay_in_ms_pos = 10;

    parse(argc, argv);
    printf("green %d %d\n", delay_in_ms_dis, delay_in_ms_pos);

    init_locks();
    init_hal("ipc:///tmp/halpubbwgreen", "ipc:///tmp/halsubbwgreen");

    pthread_t sendThread;
    int rtn = pthread_create(&sendThread, NULL, &green_send_position, NULL);
    if (rtn != 0) {
        printf("send thread creat failed\n");
        exit(1);
    }

    pthread_t recvDisThread;
    rtn = pthread_create(&recvDisThread, NULL, &green_recv_distance, NULL);
    if (rtn != 0) {
        printf("receice thread creat failed\n");
        exit(1);
    }

    pthread_t recvPosThread;
    rtn = pthread_create(&recvPosThread, NULL, &green_recv_position, NULL);
    if (rtn != 0) {
        printf("receice thread creat failed\n");
        exit(1);
    }

    pthread_t benchmarkThread;
    if (benchmarking) {
        rtn = pthread_create(&benchmarkThread, NULL, &benchmark, NULL);
        if (rtn != 0) {
            printf("benchmark thread creat failed\n");
            exit(1);
        }
    }

    pthread_join(sendThread, NULL);
    pthread_join(recvDisThread, NULL);
    pthread_join(recvPosThread, NULL);
    if (benchmarking)
        pthread_join(benchmarkThread, NULL);
}

