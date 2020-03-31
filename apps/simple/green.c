#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#include "rpc.h"
#include "xdcomms.h"
#include "gma.h"

void *send_socket = NULL;
int delay_in_ms = 10;

void *hal_init()
{
    void *ctx = xdc_ctx();
    xdc_set_out((char *)"ipc:///tmp/halpubbwgreen");
    xdc_set_in((char *)"ipc:///tmp/halsubbwgreen");

    xdc_register(position_data_encode, position_data_decode, DATA_TYP_POSITION);
    xdc_register(distance_data_encode, distance_data_decode, DATA_TYP_DISTANCE);

    return ctx;
}

void *green_send(void *args)
{
    position_datatype pos;
    pos.x = 1;
    pos.y = 1;
    pos.z = 1;

    printf("creating send thread\n");
    int count = 0;

    while (1) {
        pos.trailer.seq = 1;
        pos.trailer.rqr = 1;
        pos.trailer.oid = 1;
        pos.trailer.mid = 1;
        pos.trailer.crc = 1;

        gaps_tag  t_tag;
        uint32_t  t_mux = 1, t_sec = 1, type = DATA_TYP_POSITION;

        tag_write(&t_tag, t_mux, t_sec, type);

        if (send_socket == NULL)
            send_socket = xdc_pub_socket();
        xdc_asyn_send(send_socket, &pos, t_tag);

        printf("sent %6d: (%6.0f, %6.0f, %6.0f)\n", count, pos.x, pos.y, pos.z);
        count++;

        usleep(delay_in_ms * 1000);

        pos.x += 2;
        pos.y += 2;
        pos.z += 2;
    }

    return NULL;
}

void *green_recv_distance()
{
    printf("creating distance receive thread\n");

    gaps_tag t_tag;
    uint32_t t_mux = 2, t_sec = 2, type = DATA_TYP_DISTANCE;

    tag_write(&t_tag, t_mux, t_sec, type);
    void *socket = xdc_sub_socket(t_tag);

    distance_datatype dis;

    int count = 0;
    while (1) {
        xdc_blocking_recv(socket, &dis, &t_tag);

        printf("\t\t\t\t\t\trecv dis %6d: (%6.0f, %6.0f, %6.0f)\n", count, dis.x, dis.y, dis.z);

        count++;
    }
    zmq_close(socket);
}

void *green_recv_position()
{
    printf("creating position receive thread\n");

    gaps_tag t_tag;
    uint32_t t_mux = 2, t_sec = 2, type = DATA_TYP_POSITION;

    tag_write(&t_tag, t_mux, t_sec, type);
    void *socket = xdc_sub_socket(t_tag);

    position_datatype pos;

    int count = 0;
    while (1) {
        xdc_blocking_recv(socket, &pos, &t_tag);

        printf("\t\t\t\t\t\trecv pos %6d: (%6.0f, %6.0f, %6.0f)\n", count, pos.x, pos.y, pos.z);

        count++;
    }
    zmq_close(socket);
}

int main(int argc, char **argv)
{
    if (argc != 1 && argc != 2) {
        printf("Usage: %s <Hz>\n\
\t where <Hz> is the frequency in sending positions,\n\
\t with default 100 Hz\n", argv[0]);
        exit(1);
    }
    else if (argc == 2) {
        int hertz = atoi(argv[1]);

        if (hertz <= 0) {
            printf("bad argument %s\n", argv[1]);
            exit(1);
        }

        delay_in_ms = (int) (1000 / (double)hertz);
    }
    printf("green %d\n", delay_in_ms);

    hal_init();

    pthread_t sendThread, recvDisThread, recvPosThread;

    int rtn = pthread_create(&sendThread, NULL, &green_send, NULL);
    if (rtn != 0) {
        printf("send thread creat failed\n");
        exit(1);
    }

    rtn = pthread_create(&recvDisThread, NULL, &green_recv_distance, NULL);
    if (rtn != 0) {
        printf("receice thread creat failed\n");
        exit(1);
    }

    rtn = pthread_create(&recvPosThread, NULL, &green_recv_position, NULL);
    if (rtn != 0) {
        printf("receice thread creat failed\n");
        exit(1);
    }

    pthread_join(sendThread, NULL);
    pthread_join(recvDisThread, NULL);
    pthread_join(recvPosThread, NULL);
}

