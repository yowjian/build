#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>

#include "xdcomms.h"
#include "gma.h"

int delay_in_ms_dis = 10;
int delay_in_ms_pos = 100;

int recv_count_pos = 0;
int recv_count_dis = 0;

int send_count_pos = 0;
int send_count_dis = 0;

int elapse_seconds = 0;

pthread_mutex_t recv_lock;
pthread_mutex_t send_lock;

int display_interval = 10;         // in seconds

char benchmarking = 0;

void *benchmark()
{
    printf("creating benchmark thread\n");

    while (1) {
        sleep(1);
        elapse_seconds++;

        if (benchmarking && (elapse_seconds % display_interval == 0)) {
            printf("elapsed time  %7ds\n", elapse_seconds);

            printf("send distance %7d %8.2fHz\n", send_count_dis, send_count_dis / (double) elapse_seconds);
            printf("     position %7d %8.2fHz\n", send_count_pos, send_count_pos / (double) elapse_seconds);

            printf("recv distance %7d %8.2fHz\n", recv_count_dis, recv_count_dis / (double) elapse_seconds);
            printf("     position %7d %8.2fHz\n", recv_count_pos, recv_count_pos / (double) elapse_seconds);

            printf("\n");
        }
    }

    return NULL;
}

void init_locks()
{
    recv_count_pos = 0;

    if (pthread_mutex_init(&recv_lock, NULL) != 0)
    {
        printf("\n mutex recv init failed\n");
        exit(1);
    }

    if (pthread_mutex_init(&send_lock, NULL) != 0)
    {
        printf("\n mutex send init failed\n");
        exit(1);
    }
}

void usage()
{
    printf("Usage: <this-program> \n\
\t -b     \t benchmark mode\n\
\t -d <Hz>\t Distance Hertz (default 100 Hz)\n\
\t -p <Hz>\t Position Hertz (default 10 Hz)\n\
\t -i <period>\t Intervali in seconds to display statistics in benchmarking (default 10s)\n");
    exit(1);
}

int get_hertz(char *arg)
{
    int hertz = atoi(arg);
    if (hertz <= 0) {
        printf("bad argument %s\n", arg);
        usage();
    }
    return (int) (1000 / (double) hertz);
}

void parse(int argc, char **argv)
{
    int c;
    while ((c = getopt(argc, argv, "bd:p:i:")) != -1) {
        switch (c) {
        case 'b':
            benchmarking = 1;
            break;
        case 'd':
            delay_in_ms_dis = get_hertz(optarg);
            break;
        case 'p':
            delay_in_ms_pos = get_hertz(optarg);
            break;
        case 'i':
            display_interval = atoi(optarg);
            break;
        default:
            usage();
        }
    }
}

void *init_hal(char *out, char *in)
{
    void *ctx = xdc_ctx();

    xdc_set_out(out);
    xdc_set_in(in);

    xdc_register(position_data_encode, position_data_decode, DATA_TYP_POSITION);
    xdc_register(distance_data_encode, distance_data_decode, DATA_TYP_DISTANCE);

    return ctx;
}

void *recv_distance(uint32_t t_mux, uint32_t t_sec, uint32_t type)
{
    printf("creating distance receive thread\n");

    gaps_tag t_tag;

    tag_write(&t_tag, t_mux, t_sec, type);
    void *socket = xdc_sub_socket(t_tag);

    distance_datatype dis;

    int count = 0;
    while (1) {
        xdc_blocking_recv(socket, &dis, &t_tag);

        if (benchmarking) {
            pthread_mutex_lock(&recv_lock);
            recv_count_dis++;
            pthread_mutex_unlock(&recv_lock);
        }
        else {
            printf("\t\t\t\t\t\trecv distance %6d: (%6.0f, %6.0f, %6.0f)\n", count, dis.x, dis.y, dis.z);
            count++;
        }
    }
    zmq_close(socket);

    return NULL;
}

void *recv_position(uint32_t t_mux, uint32_t t_sec, uint32_t type)
{
    printf("creating position receive thread\n");

    gaps_tag t_tag;
    tag_write(&t_tag, t_mux, t_sec, type);

    void *socket = xdc_sub_socket(t_tag);

    position_datatype pos;

    int count = 0;
    while (1) {
        xdc_blocking_recv(socket, &pos, &t_tag);

        if (benchmarking) {
            pthread_mutex_lock(&recv_lock);
            recv_count_pos++;
            pthread_mutex_unlock(&recv_lock);
        }
        else {
            printf("\t\t\t\t\t\trecv position %6d: (%6.0f, %6.0f, %6.0f)\n", count, pos.x, pos.y, pos.z);
            count++;
        }
    }
    zmq_close(socket);

    return NULL;
}

void *send_position(uint32_t t_mux, uint32_t t_sec, uint32_t type)
{
    position_datatype pos;
    pos.x = 1;
    pos.y = 1;
    pos.z = 1;

    printf("creating send thread\n");

    void *send_pos_socket = xdc_pub_socket();
    int count = 0;

    while (1) {
        usleep(delay_in_ms_pos * 1000);

        pos.trailer.seq = 1;
        pos.trailer.rqr = 1;
        pos.trailer.oid = 1;
        pos.trailer.mid = 1;
        pos.trailer.crc = 1;

        gaps_tag  t_tag;

        tag_write(&t_tag, t_mux, t_sec, type);

        xdc_asyn_send(send_pos_socket, &pos, t_tag);

        if (benchmarking) {
            pthread_mutex_lock(&recv_lock);
            send_count_pos++;
            pthread_mutex_unlock(&recv_lock);
        }
        else {
            printf("sent position %6d: (%6.0f, %6.0f, %6.0f)\n", count, pos.x, pos.y, pos.z);
            count++;
        }

        pos.x += 2;
        pos.y += 2;
        pos.z += 2;
    }
    zmq_close(send_pos_socket);

    return NULL;
}

void *send_distance(uint32_t t_mux, uint32_t t_sec, uint32_t type)
{
    printf("creating send distance thread\n");

    distance_datatype dis;
    dis.x = 1;
    dis.y = 1;
    dis.z = 1;

    void *send_dis_socket = xdc_pub_socket();
    int count = 0;

    while (1) {
        usleep(delay_in_ms_dis * 1000);

        dis.trailer.seq = 1;
        dis.trailer.rqr = 1;
        dis.trailer.oid = 1;
        dis.trailer.mid = 1;
        dis.trailer.crc = 1;

        gaps_tag  t_tag;

        tag_write(&t_tag, t_mux, t_sec, type);

        xdc_asyn_send(send_dis_socket, &dis, t_tag);

        if (benchmarking) {
            pthread_mutex_lock(&recv_lock);
            send_count_dis++;
            pthread_mutex_unlock(&recv_lock);
        }
        else {
            printf("sent distance %6d: (%6.0f, %6.0f, %6.0f)\n", count, dis.x, dis.y, dis.z);
            count++;
        }

        dis.x += 2;
        dis.y += 2;
        dis.z += 2;
    }
    zmq_close(send_dis_socket);

    return NULL;
}

