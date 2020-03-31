#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#include "xdcomms.h"
#include "gma.h"
#include "common.h"

void *orange_send_distance(void *args)
{
    return send_distance(2, 2, DATA_TYP_DISTANCE);
}

void *orange_send_position(void *args)
{
    return send_position(2, 2, DATA_TYP_POSITION);
}

void *orange_recv_position()
{
    return recv_position(1, 1, DATA_TYP_POSITION);
}

int main(int argc, char **argv)
{
    delay_in_ms_dis = 10;
    delay_in_ms_pos = 100;

    parse(argc, argv);
    printf("orange %d %d\n", delay_in_ms_dis, delay_in_ms_pos);

    init_locks();
    init_hal("ipc:///tmp/halpubbworange", "ipc:///tmp/halsubbworange");

    pthread_t sendDisThread;
    int rtn = pthread_create(&sendDisThread, NULL, &orange_send_distance, NULL);
    if (rtn != 0) {
        printf("send distance thread creat failed\n");
        exit(1);
    }

    pthread_t sendPosThread;
    rtn = pthread_create(&sendPosThread, NULL, &orange_send_position, NULL);
    if (rtn != 0) {
        printf("send position thread creat failed\n");
        exit(1);
    }

    pthread_t recvThread;
    rtn = pthread_create(&recvThread, NULL, &orange_recv_position, NULL);
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

    pthread_join(sendDisThread, NULL);
    pthread_join(sendPosThread, NULL);
    pthread_join(recvThread, NULL);
    if (benchmarking)
        pthread_join(benchmarkThread, NULL);
}

