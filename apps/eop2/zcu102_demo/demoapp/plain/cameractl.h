#ifndef CAMERACTL_H
#define CAMERACTL_H

#include <stdint.h>

struct llat_st {
  double   lat;
  double   lon;
  double   alt;
  uint64_t ts;
};

int cam_open(char *ipaddr);
int cam_shut(void);
int cam_next(char *fbuf, int *fsz, int fmaxbytes, char *mbuf, int *msz, int mmaxbytes);

// XXX: need functions for camera commands

#endif // CAMERACTL_H

