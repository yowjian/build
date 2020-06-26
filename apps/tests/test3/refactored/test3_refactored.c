#include <stdio.h>

#pragma cle def PURPLE {"level":"purple"}
#pragma cle def ORANGE {"level":"orange"}
#pragma cle def ORANGE_SHAREABLE {"level":"orange",\
  "cdf": [\
    {"remotelevel":"purple", \
     "direction": "egress", \
     "guardhint": { "operation": "allow"}, \
     "argtaints": [["ORANGE"], ["ORANGE"]], \
     "codtaints": ["ORANGE"], \
     "rettaints": ["ORANGE_SHAREABLE"] } \
  ] }
// XXX: last annotation should list in, cod, out/ret taints re: get_ewma
// INPUT: ORANGE
// BODY: ORANGE
// OUT/RET: ORANGE_SHAREABLE
// later on, add to OUR/RET TAG_GETEWMA after autogen

#pragma cle begin ORANGE_SHAREABLE
double calc_ewma(double a, double b) {
#pragma cle begin ORANGE_SHAREABLE 
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

// blessed on orange side
#pragma cle begin ORANGE_SHAREABLE
double get_ewma() {
#pragma cle end ORANGE_SHAREABLE
  double x = get_a(); 
  double y = get_b(); 
  return calc_ewma(x,y);
}

#pragma cle begin PURPLE
int ewma_main() {
#pragma cle end PURPLE
  double ewma;
  for (int i=0; i < 10; i++) {
    ewma = get_ewma(); // conflict resolveable by wraping in RPC
    printf("%f\n", ewma);
  }
  return 0;
}

int main(int argc, char **argv) {
  return ewma_main(argc,argv);
}

// purple master: main, ewma_main
// orange slave: get_a, get_b, calc_ewma, get_ewma

