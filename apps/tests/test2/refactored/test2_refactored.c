#include <stdio.h>

#pragma cle def PURPLE {"level":"purple"}
#pragma cle def PURPLE_SHAREABLE {"level":"purple"},\
  "cdf": [\
    {"remotelevel":"orange", \
     "direction": "egress", \
     "guardhint": { "operation": "allow"}, \
     "argtaints": ["ORANGE"], \
     "codtaints": ["ORANGE", "PURPLE"], \
     "rettaints": ["PURPLE_SHAREABLE"] }\
  ] }

#pragma cle def ORANGE {"level":"orange"},\
  "cdf": [\
    {"remotelevel":"purple", \
     "direction": "egress", \
     "guardhint": { "operation": "allow"}}\
  ] }

double calc_ewma(double a, double b) {
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
#pragma cle begin PURPLE
  static double b = 1.0;
#pragma cle end PURPLE
  b += b;
  return b;
}

#pragma cle begin PURPLE_SHAREABLE
double get_ewma(double x) 
#pragma cle end PURPLE_SHAREABLE
{
  double y = get_b();
  return calc_ewma(x,y);
}

int ewma_main() {
  double x;
  double y;
#pragma cle begin ORANGE
  double ewma;
#pragma cle end ORANGE
  for (int i=0; i < 10; i++) {
    x = get_a();
    ewma = get_ewma(x); // wrapping in RPC will solve conflict
    printf("%f\n", ewma);
  }
  return 0;
}

int main(int argc, char **argv) {
  return ewma_main(argc,argv);
}

// orange master: main, ewma_main, get_a
// purple slave:  get_b, calc_ewma, get_ewma
