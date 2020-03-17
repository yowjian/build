#ifndef GMA_HEADER_FILE
#define GMA_HEADER_FILE

extern "C" {

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define DATA_TYP_POSITION    1
#define DATA_TYP_DISTANCE    2

/* Data structure: PNT */
typedef struct _position_datatype {
    double x;
    double y;
    double z;
} position_datatype;

typedef struct _distance_datatype {
    double dx;
    double dy;
    double dz;
} distance_datatype;

extern void position_print (position_datatype *);
extern void position_data_encode (uint8_t *, size_t *, uint8_t *, size_t *);
extern void position_data_decode (uint8_t *, size_t *, uint8_t *, size_t *);

extern void distance_print (distance_datatype *);
extern void distance_data_encode (uint8_t *, size_t *, uint8_t *, size_t *);
extern void distance_data_decode (uint8_t *, size_t *, uint8_t *, size_t *);

// Guard Provisioning calls to be added here
}
#endif
