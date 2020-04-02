#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#include "xdcomms.h"
#include "gma.h"
#include "common.h"

void *green_send_position(void *args)
{
    return gaps_write(1, 1, DATA_TYP_POSITION, PORT_GREEN_TO_ORANGE_POS);
}

void *green_recv_distance()
{
    return gaps_read(2, 2, DATA_TYP_DISTANCE, PORT_ORANGE_TO_GREEN_DIS);
}

void *green_recv_position()
{
    return gaps_read(2, 2, DATA_TYP_POSITION, PORT_ORANGE_TO_GREEN_POS);
}

int main(int argc, char **argv)
{
    // defaults
    init_stats(0, 100);
    strcpy(ipc_pub, "ipc:///tmp/halpubbwgreen");
    strcpy(ipc_sub, "ipc:///tmp/halsubbwgreen");

    parse(argc, argv);
    printf("green %lli %lli\n", stats[DIR_SEND][TYPE_DIS].delay, stats[DIR_SEND][TYPE_POS].delay);

    init_locks();
    init_hal();

    pthread_t recvDisThread;
    int rtn = pthread_create(&recvDisThread, NULL, &green_recv_distance, NULL);
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

    pthread_t sendThread;
    rtn = pthread_create(&sendThread, NULL, &green_send_position, NULL);
    if (rtn != 0) {
        printf("send thread creat failed\n");
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

    show_stats();
    exit(0);
}

