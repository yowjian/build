#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#include "xdcomms.h"
#include "gma.h"
#include "common.h"

void *orange_send_distance(void *args)
{
    return gaps_write(2, 2, DATA_TYP_DISTANCE, PORT_ORANGE_TO_GREEN_DIS);
}

void *orange_send_position(void *args)
{
    return gaps_write(2, 2, DATA_TYP_POSITION, PORT_ORANGE_TO_GREEN_POS);
}

void *orange_recv_position()
{
    return gaps_read(1, 1, DATA_TYP_POSITION, PORT_GREEN_TO_ORANGE_POS);
}

int main(int argc, char **argv)
{
    // defaults
    init_stats(10, 100);
    strcpy(ipc_pub, "ipc:///tmp/halpubbworange");
    strcpy(ipc_sub, "ipc:///tmp/halsubbworange");

    parse(argc, argv);
    printf("orange %lli %lli\n", stats[DIR_SEND][TYPE_DIS].delay, stats[DIR_SEND][TYPE_POS].delay);

    init_locks();
    init_hal();

    pthread_t recvThread;
    int rtn = pthread_create(&recvThread, NULL, &orange_recv_position, NULL);
    if (rtn != 0) {
        printf("receice thread creat failed\n");
        exit(1);
    }

    pthread_t sendDisThread;
    rtn = pthread_create(&sendDisThread, NULL, &orange_send_distance, NULL);
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

    show_stats();
    exit(0);
}

