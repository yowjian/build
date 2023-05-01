#include "orange_rpc.h"
#include <stdio.h>

#pragma cle def PURPLE {"level":"purple"}
#pragma cle def PURPLE_SHAREABLE { "level": "purple", \
  "cdf": [ \
    {"remotelevel": "orange", \
     "direction": "bidirectional", \
     "guarddirective": { "operation": "allow"} } \
    ]}

#pragma cle def XDLINKAGE_GET_EWMA {"level":"purple",	\
  "cdf": [\
    {"remotelevel":"orange", \
     "direction": "bidirectional", \
     "guarddirective": { "operation": "allow"}, \
     "argtaints": [["TAG_REQUEST_GET_EWMA"]], \
     "codtaints": ["PURPLE", "PURPLE_SHAREABLE"], \
     "rettaints": ["TAG_RESPONSE_GET_EWMA"] },\
    {"remotelevel":"purple", \
     "direction": "bidirectional", \
     "guarddirective": { "operation": "allow"}, \
     "argtaints": [["TAG_REQUEST_GET_EWMA"]], \
     "codtaints": ["PURPLE", "PURPLE_SHAREABLE"], \
     "rettaints": ["TAG_RESPONSE_GET_EWMA"] }\
  ] }

#pragma cle def ORANGE {"level":"orange",\
  "cdf": [\
    {"remotelevel":"purple", \
     "direction": "egress", \
     "guarddirective": { "operation": "allow"}}\
  ] }

#pragma cle def EWMA_MAIN {"level":"orange",\
  "cdf": [\
    {"remotelevel":"orange", \
     "direction": "bidirectional", \
     "guarddirective": { "operation": "allow"}, \
     "argtaints": [], \
     "codtaints": ["ORANGE", "TAG_REQUEST_GET_EWMA", "TAG_RESPONSE_GET_EWMA"], \
     "rettaints": ["ORANGE"] \
    } \
  ] }


double get_a() {
#pragma cle begin ORANGE
#pragma clang attribute push (__attribute__((annotate("ORANGE"))), apply_to = any(function,type_alias,record,enum,variable(unless(is_parameter)),field))
  static double a = 0.0;
#pragma clang attribute pop
#pragma cle end ORANGE
  a += 1;
  return a;
}



#pragma cle begin EWMA_MAIN
#pragma clang attribute push (__attribute__((annotate("EWMA_MAIN"))), apply_to = any(function,type_alias,record,enum,variable(unless(is_parameter)),field))
int ewma_main() {
#pragma clang attribute pop
#pragma cle end EWMA_MAIN
  double x;
  double y;
  double ewma;
  for (int i=0; i < 10; i++) {
    x = get_a();
    y = x;
    ewma = _err_handle_rpc_get_ewma(y);
    printf("%f\n", ewma);
  }
  return 0;
}

int main() {
  _master_rpc_init();
  return ewma_main();
}
