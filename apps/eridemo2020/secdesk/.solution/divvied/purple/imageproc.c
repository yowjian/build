#include "imageproc.h"

/* Once the stub is filled out, the loaded recongizer model must be PURPLE */
#pragma cle def PURPLE {"level":"purple"}

#pragma cle def XDLINKAGE_RECOGNIZE {"level":"purple",\
  "cdf": [\
    {"remotelevel":"orange", \
     "direction": "bidirectional", \
     "guardhint": {"operation": "allow"}, \
     "argtaints": [["TAG_REQUEST_RECOGNIZE"]], \
     "codtaints": ["PURPLE"], \
     "rettaints": ["TAG_RESPONSE_RECOGNIZE"] \
    } \
  ] }

#pragma cle def XDLINKAGE_START_RECOGNIZER {"level":"purple",\
  "cdf": [\
    {"remotelevel":"orange", \
     "direction": "bidirectional", \
     "guardhint": {"operation": "allow"}, \
     "argtaints": [["TAG_REQUEST_START_RECOGNIZER"]], \
     "codtaints": ["PURPLE"], \
     "rettaints": ["TAG_RESPONSE_START_RECOGNIZER"] \
    } \
  ] }
  
#pragma cle def XDLINKAGE_STOP_RECOGNIZER {"level":"purple",\
  "cdf": [\
    {"remotelevel":"orange", \
     "direction": "bidirectional", \
     "guardhint": {"operation": "allow"}, \
     "argtaints": [["TAG_REQUEST_STOP_RECOGNIZER"]], \
     "codtaints": ["PURPLE"], \
     "rettaints": ["TAG_RESPONSE_STOP_RECOGNIZER"] \
    } \
  ] }
 

#pragma cle begin XDLINKAGE_START_RECOGNIZER
int start_recognizer(void) {
#pragma cle end XDLINKAGE_START_RECOGNIZER
  return 0;
}

#pragma cle begin XDLINKAGE_STOP_RECOGNIZER
int stop_recognizer(void) {
#pragma cle end XDLINKAGE_STOP_RECOGNIZER
  return 0;
}

#pragma cle begin XDLINKAGE_RECOGNIZE
int recognize(double embedding[static 128]) {
#pragma cle end XDLINKAGE_RECOGNIZE
  double d[128];
  memset(d,0,128*sizeof(double));
  int i = memcmp(d,embedding,128*sizeof(double));
  return 666;
  /* return -1; */
}

