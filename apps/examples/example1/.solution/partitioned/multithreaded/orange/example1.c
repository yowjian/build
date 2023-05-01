#include "orange_rpc.h"
#include <stdio.h>
#pragma cle def PURPLE {"level":"purple"}
#pragma cle def ORANGE {"level":"orange",\
  "cdf": [\
    {"remotelevel":"purple", \
     "direction": "egress", \
     "guarddirective": { "operation": "allow"}}\
  ] }
#pragma cle def EWMA_MAIN {"level":"purple",\
  "cdf": [\
    {"remotelevel":"purple", \
     "direction": "bidirectional", \
     "guarddirective": { "operation": "allow"}, \
     "argtaints": [], \
     "codtaints": ["PURPLE", "TAG_RESPONSE_GET_A"], \
     "rettaints": ["PURPLE"] \
    } \
  ] }
#pragma cle def XDLINKAGE_GET_A {"level":"orange",\
  "cdf": [\
    {"remotelevel":"purple", \
     "direction": "bidirectional", \
     "guarddirective": { "operation": "allow"}, \
     "argtaints": [], \
     "codtaints": ["ORANGE"], \
     "rettaints": ["TAG_RESPONSE_GET_A"], \
     "idempotent": true, \
     "num_tries": 30, \
     "timeout": 1000 \
    }, \
    {"remotelevel":"orange", \
     "direction": "bidirectional", \
     "guarddirective": { "operation": "allow"}, \
     "argtaints": [], \
     "codtaints": ["ORANGE"], \
     "rettaints": ["TAG_RESPONSE_GET_A"] \
    } \
  ] }
#pragma cle begin XDLINKAGE_GET_A 
#pragma clang attribute push (__attribute__((annotate("XDLINKAGE_GET_A"))), apply_to = any(function,type_alias,record,enum,variable(unless(is_parameter)),field))
double get_a() {
#pragma clang attribute pop
#pragma cle end XDLINKAGE_GET_A 
#pragma cle begin ORANGE
#pragma clang attribute push (__attribute__((annotate("ORANGE"))), apply_to = any(function,type_alias,record,enum,variable(unless(is_parameter)),field))
  static double a = 0.0;
#pragma clang attribute pop
#pragma cle end ORANGE
  a += 1;
  return a;
}
int main(int argc, char *argv[]) {
  return _slave_rpc_loop();
}