#ifndef _IMAGEPROC_H_
#define _IMAGEPROC_H_

#include <string.h>

void start_recognizer(void);
void stop_recognizer(void);

int recognize(double embedding[static 128]);

#endif /* _IMAGEPROC_H_ */

