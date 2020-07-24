#include "imageproc.h"

void start_imageprocessor(void) {
}

void stop_imageprocessor(void) {
}

void start_recognizer(void) {
}

void stop_recognizer(void) {
}

int get_features(char *imagefile, double embedding[static 128]) {
  memset(embedding,0,128*sizeof(double));
  return 0;
}

int recognize(double embedding[static 128]) {
  double d = 0;
  for (int i=0; i<128; i++) d += embedding[i];
  return 666;
  /* return -1; */
}

