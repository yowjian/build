#pragma cle def ORANGE_NONSHAREABLE {"level":"orange"}

#pragma cle def GREEN_NONSHAREABLE {"level":"green"}

#pragma cle def ORANGE_SHAREABLE {"level":"orange",\
  "cdf": [\
    {"remotelevel":"green", \
     "direction": "bidirectional", \
     "guarddirective": { "operation": "allow"} \
    } \
  ] }

#pragma cle def GREEN_SHAREABLE {"level":"green",\
  "cdf": [\
    {"remotelevel":"orange", \
     "direction": "bidirectional", \
     "guarddirective": { "operation": "allow"} \
    } \
  ] }

#pragma cle def XDLINKAGE_INIT_A {"level":"green",\
  "cdf": [\
    {"remotelevel":"orange", \
     "direction": "bidirectional", \
     "guarddirective": { "operation": "allow"}, \
     "argtaints": [], \
     "codtaints": ["GREEN_NONSHAREABLE", "GREEN_SHAREABLE"], \
     "rettaints": ["TAG_RESPONSE_INIT_A"] \
    }, \
    {"remotelevel":"green", \
     "direction": "bidirectional", \
     "guarddirective": { "operation": "allow"}, \
     "argtaints": [], \
     "codtaints": ["GREEN_NONSHAREABLE", "GREEN_SHAREABLE"], \
     "rettaints": ["TAG_RESPONSE_INIT_A"] \
    } \
  ] }

#pragma cle def XDLINKAGE_DISTANCEA {"level":"green",\
   "cdf": [\
    {"remotelevel":"orange", \
     "direction": "bidirectional", \
     "guarddirective": { "operation": "allow"}, \
     "argtaints": [["TAG_REQUEST_DISTANCEA"],["TAG_REQUEST_DISTANCEA"]], \
     "codtaints": ["GREEN_NONSHAREABLE", "GREEN_SHAREABLE"], \
     "rettaints": ["TAG_RESPONSE_DISTANCEA"] \
    }, \
    {"remotelevel":"green", \
     "direction": "bidirectional", \
     "guarddirective": { "operation": "allow"}, \
     "argtaints": [["TAG_REQUEST_DISTANCEA"],["TAG_REQUEST_DISTANCEA"]], \
     "codtaints": ["GREEN_NONSHAREABLE", "GREEN_SHAREABLE"], \
     "rettaints": ["TAG_RESPONSE_DISTANCEA"] \
    } \
  ] }

#pragma cle def COERCE_MAIN {"level":"orange",\
   "cdf": [\
    {"remotelevel":"orange", \
     "direction": "bidirectional", \
     "guarddirective": { "operation": "allow"}, \
     "argtaints": [], \
     "codtaints": ["ORANGE_NONSHAREABLE", "ORANGE_SHAREABLE"], \
     "rettaints": [] \
    } \
  ] }

#ifdef USE_ONEAPI
#include <CL/sycl.hpp>
#include <iostream>
#else
#include <stdlib.h>
#include <stdio.h>
#endif

#define MAX_FLOAT 1e99
#define MATRIX_SIZE 50

#ifdef USE_ONEAPI
using Matrix = sycl::accessor<float,2,sycl::access_mode::read_write,sycl::target::host_buffer>;
#else
typedef float Matrix[MATRIX_SIZE][MATRIX_SIZE];
#endif


Matrix *getA(int init) {
#pragma cle begin GREEN_NONSHAREABLE
#ifdef USE_ONEAPI
  static sycl::buffer<float,2> ABuffer(sycl::range<2>(MATRIX_SIZE, MATRIX_SIZE));
  static auto A = ABuffer.get_access<sycl::access::mode::read_write>();
#else
  static Matrix A;
#endif
#pragma cle end GREEN_NONSHAREABLE

  if (init != 0) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
      for (int j = 0; j < MATRIX_SIZE; j++) {
        A[i][j] = 1.0 + i * 0.5 + j * 2.5;
      }
    }
  }
  return &A;
}

Matrix *getB(int init) {
#pragma cle begin ORANGE_NONSHAREABLE
#ifdef USE_ONEAPI
  static sycl::buffer<float,2> BBuffer(sycl::range<2>(MATRIX_SIZE, MATRIX_SIZE));
  static auto B = BBuffer.get_access<sycl::access::mode::read_write>();
#else
  static Matrix B;
#endif
#pragma cle end ORANGE_NONSHAREABLE

  if (init != 0) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
      for (int j = 0; j < MATRIX_SIZE; j++) {
        B[i][j] = 3.0 + i * j * 4.8;
      }
    }
  }
  return &B;
}


Matrix *getAllPairsShortestPathsA(int compute) {
#pragma cle begin GREEN_NONSHAREABLE
#ifdef USE_ONEAPI
  static sycl::buffer<float,2> distancesABuffer(sycl::range<2>(MATRIX_SIZE, MATRIX_SIZE));
  static auto distancesA = distancesABuffer.get_access<sycl::access::mode::read_write>();
#else
  static Matrix distancesA;
#endif
#pragma cle end GREEN_NONSHAREABLE

  if (compute == 0) { return &distancesA; }

  for (int i = 0; i < MATRIX_SIZE; i++) {
    for (int j = 0; j < MATRIX_SIZE; j++) {
      distancesA[i][j] = (*getA(0))[i][j];
    }
  }

#ifdef USE_ONEAPI
  sycl::queue gpu_queue(sycl::gpu_selector{});
  //sycl::queue gpu_queue;
  gpu_queue.submit([&](sycl::handler &h) {
    auto buffaccAdist = distancesABuffer.get_access<sycl::access::mode::read_write>(h);
    h.parallel_for(sycl::nd_range<3>(sycl::range<3>(MATRIX_SIZE, MATRIX_SIZE, MATRIX_SIZE),
                                     sycl::range<3>(MATRIX_SIZE, MATRIX_SIZE, MATRIX_SIZE)),
                                     [=](sycl::nd_item<3> item)
      {
        int k = item.get_global_id(0);
        int i = item.get_global_id(1);
        int j = item.get_global_id(2);
        if (buffaccAdist[i][j] > (buffaccAdist[i][k] + buffaccAdist[k][j]) && (buffaccAdist[k][j] >= MAX_FLOAT && buffaccAdist[i][k] >= MAX_FLOAT))
        {
           buffaccAdist[i][j] = buffaccAdist[i][k] + buffaccAdist[k][j];
        }
      });
    });
#else
  //Floyd Warshall algorithm
  for (int k = 0; k < MATRIX_SIZE; k ++) {
    for (int i = 0; i < MATRIX_SIZE; i ++) {
      for (int j = 0; j < MATRIX_SIZE; j ++) {
	if (distancesA[i][j] > (distancesA[i][k] + distancesA[k][j]) &&
	    (distancesA[k][j] >= MAX_FLOAT && distancesA[i][k] >= MAX_FLOAT)) {
	  distancesA[i][j] = distancesA [i][k] + distancesA[k][j];
	}
      }
    }
  }
#endif
  return &distancesA;
}



Matrix *getAllPairsShortestPathsB(int compute) {
#pragma cle begin ORANGE_NONSHAREABLE
#ifdef USE_ONEAPI
  static sycl::buffer<float,2> distancesBBuffer(sycl::range<2>(MATRIX_SIZE, MATRIX_SIZE));
  static auto distancesB = distancesBBuffer.get_access<sycl::access::mode::read_write>();
#else
  static Matrix distancesB;
#endif
#pragma cle end ORANGE_NONSHAREABLE

  if (compute == 0) { return &distancesB; }

  for (int i = 0; i < MATRIX_SIZE; i++) {
    for (int j = 0; j < MATRIX_SIZE; j++) {
      distancesB[i][j] = (*getB(0))[i][j];
    }
  }

#ifdef USE_ONEAPI
  sycl::queue gpu_queue(sycl::gpu_selector{});
  //sycl::queue gpu_queue;
  gpu_queue.submit([&](sycl::handler &h) {
    auto buffaccBdist = distancesBBuffer.get_access<sycl::access::mode::read_write>(h);
    h.parallel_for(sycl::nd_range<3>(sycl::range<3>(MATRIX_SIZE, MATRIX_SIZE, MATRIX_SIZE),
                                     sycl::range<3>(MATRIX_SIZE, MATRIX_SIZE, MATRIX_SIZE)),
                                     [=](sycl::nd_item<3> item)
      {
        int k = item.get_global_id(0);
        int i = item.get_global_id(1);
        int j = item.get_global_id(2);
        if (buffaccBdist[i][j] > (buffaccBdist[i][k] + buffaccBdist[k][j]) && (buffaccBdist[k][j] >= MAX_FLOAT && buffaccBdist[i][k] >= MAX_FLOAT))
        {
           buffaccBdist[i][j] = buffaccBdist[i][k] + buffaccBdist[k][j];
        }
      });
    });
#else
  //Floyd Warshall algorithm
  for (int k = 0; k < MATRIX_SIZE; k ++) {
    for (int i = 0; i < MATRIX_SIZE; i ++) {
      for (int j = 0; j < MATRIX_SIZE; j ++) {
	if (distancesB[i][j] > (distancesB[i][k] + distancesB[k][j]) &&
	    (distancesB[k][j] >= MAX_FLOAT && distancesB[i][k] >= MAX_FLOAT)) {
	  distancesB[i][j] = distancesB [i][k] + distancesB[k][j];
	}
      }
    }
  }
#endif
  return &distancesB;
}

// blessed to declassify and share a single distance
#pragma cle begin XDLINKAGE_INIT_A
int init_A(void) {
#pragma cle end XDLINKAGE_INIT_A
#pragma cle begin GREEN_SHAREABLE
  int ret = 0;
#pragma cle end GREEN_SHAREABLE
  getA(1);
  getAllPairsShortestPathsA(1);
  return ret;
}

int init_B(void) {
  getB(1);
  getAllPairsShortestPathsB(1);
  return 0;
}
 


#pragma cle begin XDLINKAGE_DISTANCEA
float distanceA(int x, int y) {
#pragma cle end XDLINKAGE_DISTANCEA
#pragma cle begin GREEN_SHAREABLE
  float ret = 0.0;
#pragma cle end GREEN_SHAREABLE
  ret = (*getAllPairsShortestPathsA(0))[x][y];
  return ret;
}


float distanceB(int x, int y) {
  return (*getAllPairsShortestPathsB(0))[x][y];
} 




// running on B
// A side has client loop only
#pragma cle begin COERCE_MAIN
void do_main(void) {
#pragma cle end COERCE_MAIN

  // init_A will be wrapped in xd rpc
  int ret1 = init_A();
  int ret2 = init_B();

  float dA;
#pragma cle begin ORANGE_SHAREABLE
  int n1 = 5;
  int n2 = 4;
#pragma cle end ORANGE_SHAREABLE

#pragma cle begin ORANGE_NONSHAREABLE
  float dB;
  int n3 = 5;
  int n4 = 6;
#pragma cle end ORANGE_NONSHAREABLE

  // distanceA will be wrapped in xd rpc
  dA = distanceA(n1,n2);
  dB = distanceB(n3,n4);

#ifdef USE_ONEAPI
  std::cout << "distance a: " << dA << std::endl;
  std::cout << "distance b: " << dB << std::endl;
#else
  printf("Distance a = %f\n", dA);
  printf("Distance b = %f\n", dB);
#endif
}


int main(int argc, char * argv[]) {
  do_main();
  return 0;
}