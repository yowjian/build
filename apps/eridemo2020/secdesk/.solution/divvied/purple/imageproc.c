#include "imageproc.h"

/* Once the stub is filled out, the loaded recongizer model must be PURPLE */
#pragma cle def PURPLE {"level":"purple"}

#pragma cle def XDLINKAGE_RECOGNIZE {"level":"purple",\
  "cdf": [\
    {"remotelevel":"orange", \
     "direction": "bidirectional", \
     "guardhint": {"operation": "allow"}, \
     "argtaints": ["TAG_REQUEST_RECOGNIZE"], \
     "codtaints": ["PURPLE"], \
     "rettaints": ["TAG_RESPONSE_RECOGNIZE"] \
    } \
  ] }
  

void start_recognizer(void) {
}

void stop_recognizer(void) {
}

#pragma cle begin XDLINKAGE_RECOGNIZE
int recognize(double embedding[static 128]) {
#pragma cle end XDLINKAGE_RECOGNIZE
  return 666;
  /* return -1; */
}
