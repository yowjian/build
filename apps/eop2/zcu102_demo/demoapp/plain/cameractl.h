#ifndef CAMERACTL_H
#define CAMERACTL_H

#include <stdint.h>
#include <pthread.h>

struct llat_st {
  double   lat;
  double   lon;
  double   alt;
  uint64_t ts;
};

#define MAX_FRAME_BUF   64000
#define MAX_MDATA_BUF   sizeof(struct llat_st)

struct framebuf_st {
  pthread_mutex_t flk;
  char            newf;
  size_t          size;
  char            data[MAX_FRAME_BUF];
};

int cam_open(char *ipaddr);
int cam_shut(void);
int cam_next(char *fbuf, int *fsz, int fmaxbytes, char *mbuf, int *msz, int mmaxbytes);

// XXX: need functions for camera commands

#endif // CAMERACTL_H

