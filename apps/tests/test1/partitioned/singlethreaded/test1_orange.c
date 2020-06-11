#include <stdio.h>
#include "test1_orange_rpc.h"

#pragma cle def ORANGE {"level":"orange",\
  "cdf": [\
    {"remotelevel":"==purple", \
     "direction": "egress", \
     "guardhint": { "oneway": "true"}}\
  ] }

double get_a() {
#pragma cle begin ORANGE
  static double a = 0.0;
#pragma cle end ORANGE
  a += 1;
  return a;
}

int main(int argc, char **argv) {
  return _slave_rpc_loop();
}
