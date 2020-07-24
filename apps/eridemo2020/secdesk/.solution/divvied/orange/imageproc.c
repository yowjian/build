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
 
void start_imageprocessor(void) {
}

void stop_imageprocessor(void) {
}

#pragma cle begin ORANGE 
int get_features(char *imagefile, double embedding[static 128]) {
#pragma cle end ORANGE 
  memset(embedding,0,128*sizeof(double));
  return 0;
}

