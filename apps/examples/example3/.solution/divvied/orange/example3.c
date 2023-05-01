#include <stdio.h>

#pragma cle def PURPLE {"level":"purple"}
#pragma cle def ORANGE {"level":"orange"}
#pragma cle def ORANGE_SHAREABLE {"level":"orange",\
  "cdf": [\
    {"remotelevel":"purple", \
     "direction": "egress", \
     "guarddirective": { "operation": "allow"}}\
  ] }
#pragma cle def EWMA_SHAREABLE {"level":"orange",\
  "cdf": [\
    {"remotelevel":"orange", \
     "direction": "egress", \
     "guarddirective": { "operation": "allow"}, \
     "argtaints": [["ORANGE"], ["ORANGE"]], \
     "codtaints": ["ORANGE", "ORANGE_SHAREABLE"], \
     "rettaints": ["ORANGE_SHAREABLE"] } \
 ] }

#pragma cle def XDLINKAGE_GET_EWMA {"level":"orange",	\
  "cdf": [\
    {"remotelevel":"orange", \
     "direction": "bidirectional", \
     "guarddirective": { "operation": "allow"}, \
     "argtaints": [], \
     "codtaints": ["ORANGE", "ORANGE_SHAREABLE"], \
     "rettaints": ["TAG_RESPONSE_GET_EWMA"] },\
    {"remotelevel":"purple", \
     "direction": "bidirectional", \
     "guarddirective": { "operation": "allow"}, \
     "argtaints": [], \
     "codtaints": ["ORANGE", "ORANGE_SHAREABLE"], \
     "rettaints": ["TAG_RESPONSE_GET_EWMA"] }\
  ] }

#pragma cle def EWMA_MAIN {"level":"purple",\
  "cdf": [\
    {"remotelevel":"purple", \
     "direction": "bidirectional", \
     "guarddirective": { "operation": "allow"}, \
     "argtaints": [], \
     "codtaints": ["PURPLE", "TAG_REQUEST_GET_EWMA", "TAG_RESPONSE_GET_EWMA"], \
     "rettaints": ["PURPLE"] \
    } \
  ] }

#pragma cle begin EWMA_SHAREABLE
double calc_ewma(double a, double b) {
#pragma cle end EWMA_SHAREABLE
  const  double alpha = 0.25;
  static double c = 0.0;
  c = alpha * (a + b) + (1 - alpha) * c;
  return c;
}

double get_a() {
#pragma cle begin ORANGE
  static double a = 0.0;
#pragma cle end ORANGE
  a += 1;
  return a;
}

double get_b() {
#pragma cle begin ORANGE
  static double b = 1.0;
#pragma cle end ORANGE
  b += b;
  return b;
}

#pragma cle begin XDLINKAGE_GET_EWMA
double get_ewma() {
#pragma cle end XDLINKAGE_GET_EWMA
  double x = get_a(); 
  double y = get_b(); 
  return calc_ewma(x,y);
}



// purple master: main, ewma_main