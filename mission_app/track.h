#ifndef _TRACK_H_
#define _TRACK_H_

#include <time.h>

typedef struct _track_data {
    time_t timestamp;
    double lon;
    double lat;
    double hae;    // height above ellipsoid
    double speed;
    double course; // "340.48177374151624" />
} track_data_t;

typedef struct _rf_mti {
    double mti;
} rf_mti_t;

typedef struct _rf_track {
	track_data_t track;
} rf_track_t;

typedef struct _rf_sensor {
    double azimuth;
    double range;
} rf_sensor_t;

typedef struct _global_fix {
    double x;
    double y;
    double z;
} global_fix_t;

typedef struct _eo_ir_video {
	double data[16];
} eo_ir_video_t;

typedef struct _eo_ir_track {
	track_data_t track;
} eo_ir_track_t;

typedef struct _pnt_src {
	global_fix_t position_fix;
	long time;
} pnt_position_t;

track_data_t *get_track_data();



#endif /*_TARCK_H_*/
