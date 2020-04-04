#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#include "xdcomms.h"
#include "gma.h"
#include "common.h"
#include "utils.h"

int main(int argc, char **argv)
{
    // defaults
    init_stats(10, 100);
    strcpy(ipc_pub, "ipc:///tmp/halpubbworange");
    strcpy(ipc_sub, "ipc:///tmp/halsubbworange");

    parse(argc, argv);

    init_locks();
    init_hal();

    pthread_t benchmarkThread;
    int rtn = pthread_create(&benchmarkThread, NULL, &benchmark, NULL);
    if (rtn != 0) {
        printf("benchmark thread creat failed\n");
        exit(1);
    }

    show_stats();
    exit(0);
}

