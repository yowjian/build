#ifndef _IMAGEPROC_H_
#define _IMAGEPROC_H_

#include <string.h>

int start_imageprocessor(void);
int stop_imageprocessor(void);
int start_recognizer(void);
int stop_recognizer(void);

int get_features(char *imagefile, double embedding[static 128]);
int recognize(double embedding[static 128]);

#endif /* _IMAGEPROC_H_ */

