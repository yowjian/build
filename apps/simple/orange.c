#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#include "rpc.h"
#include "xdcomms.h"
#include "gma.h"

void *ctx;
void *send_socket = NULL;
int delay_in_ms_dis = 1000;
int delay_in_ms_pos = 1000;

void *hal_init()
{
  void *ctx = xdc_ctx();
  xdc_set_out((char *)"ipc:///tmp/halpubbworange");
  xdc_set_in((char *)"ipc:///tmp/halsubbworange");

  xdc_register(position_data_encode, position_data_decode, DATA_TYP_POSITION);
  xdc_register(distance_data_encode, distance_data_decode, DATA_TYP_DISTANCE);

  return ctx;
}

void *orange_send_distance(void *args)
{
  distance_datatype dis;
  dis.x = 2;
  dis.y = 2;
  dis.z = 2;

  printf("creating send thread\n");
  int count = 0;

  while (1) {
    dis.trailer.seq = 2;
    dis.trailer.rqr = 2;
    dis.trailer.oid = 2;
    dis.trailer.mid = 2;
    dis.trailer.crc = 2;

    gaps_tag  t_tag;
    uint32_t  t_mux = 2, t_sec = 2, type = DATA_TYP_DISTANCE;

    tag_write(&t_tag, t_mux, t_sec, type);

    if (send_socket == NULL)
      send_socket = xdc_pub_socket(ctx);
    xdc_asyn_send(send_socket, &dis, t_tag);

    printf("sent dis %6d: (%6.0f, %6.0f, %6.0f)\n", count, dis.x, dis.y, dis.z);
    count++;
    
    usleep(delay_in_ms_dis * 1000);

    dis.x += 2;
    dis.y += 2;
    dis.z += 2;
  }

  return NULL;
}

void *orange_send_position(void *args)
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
    uint32_t  t_mux = 2, t_sec = 2, type = DATA_TYP_POSITION;

    tag_write(&t_tag, t_mux, t_sec, type);

    if (send_socket == NULL)
      send_socket = xdc_pub_socket(ctx);
    xdc_asyn_send(send_socket, &pos, t_tag);

    printf("sent pos %6d: (%6.0f, %6.0f, %6.0f)\n", count, pos.x, pos.y, pos.z);
    count++;
    
    usleep(delay_in_ms_pos * 1000);

    pos.x += 2;
    pos.y += 2;
    pos.z += 2;
  }

  return NULL;
}

void *orange_recv()
{
  printf("creating receive thread\n");

  gaps_tag t_tag;
  uint32_t  t_mux = 1, t_sec = 1, type = DATA_TYP_POSITION;

  tag_write(&t_tag, t_mux, t_sec, type);
  void *socket = xdc_sub_socket(t_tag);

  position_datatype pos;

  int count = 0;
  while (1) {
    xdc_blocking_recv(socket, &pos, &t_tag);

    printf("\t\t\t\t\trecv %6d: (%6.0f, %6.0f, %6.0f)\n", count, pos.x, pos.y, pos.z);

    count++;
  }
  zmq_close(socket);

  return NULL;
}

int main(int argc, char **argv)
{
  if (argc >= 3) {
    delay_in_ms_dis = atoi(argv[1]);
    if (delay_in_ms_dis <= 0) {
      printf("bad argument %s\n", argv[1]);
      exit(1);
    }

    delay_in_ms_pos = atoi(argv[2]);
    if (delay_in_ms_pos <= 0) {
      printf("bad argument %s\n", argv[2]);
      exit(1);
    }
  }

  printf("orange %d %d\n", delay_in_ms_dis, delay_in_ms_pos);
  ctx = hal_init();

  pthread_t sendDisThread, sendPosThread, recvThread;

  int rtn = pthread_create(&sendDisThread, NULL, &orange_send_distance, NULL);
  if (rtn != 0) {
    printf("send distance thread creat failed\n");
    exit(1);
  }

  rtn = pthread_create(&sendPosThread, NULL, &orange_send_position, NULL);
  if (rtn != 0) {
    printf("send position thread creat failed\n");
    exit(1);
  }
  
  rtn = pthread_create(&recvThread, NULL, &orange_recv, NULL);
  if (rtn != 0) {
    printf("receice thread creat failed\n");
    exit(1);
  }

  pthread_join(sendDisThread, NULL);
  pthread_join(sendPosThread, NULL);
  pthread_join(recvThread, NULL);  
}

