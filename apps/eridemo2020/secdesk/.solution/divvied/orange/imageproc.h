#ifndef _IMAGEPROC_H_
#define _IMAGEPROC_H_

#include <string.h>

void start_imageprocessor(void);
void stop_imageprocessor(void);

int get_features(char *imagefile, double embedding[static 128]);

#endif /* _IMAGEPROC_H_ */

