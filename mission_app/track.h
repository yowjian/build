#ifndef _TRACK_H_
#define _TRACK_H_

#include <time.h>

typedef enum _message_type {
    TYPE_TRACK_DATA = 0,
	TYPE_RF_MTI = 1,
	TYPE_RF_TRACK = 2,
	TYPE_RF_SENSOR = 3,
	TYPE_GLOBAL_FIX = 4,
	TYPE_EO_IR_VIDEO = 5,
	TYPE_EO_IR_TRACK = 6,
	TYPE_PNT_POSITION = 7,
	TYPE_PNT_TIME = 8,
    NUM_COT_TYPES = 9,
} message_type_t;

typedef struct _track_data {
	message_type_t type;
    time_t timestamp;
    double lon;
    double lat;
    double hae;    // height above ellipsoid
    double speed;
    double course; // "340.48177374151624" />
} track_data_t;

typedef struct _rf_mti {
	message_type_t type;
    double mti;
} rf_mti_t;

typedef struct _rf_track {
	message_type_t type;
	track_data_t track;
} rf_track_t;

typedef struct _rf_sensor {
	message_type_t type;
    double azimuth;
    double range;
} rf_sensor_t;

typedef struct _global_fix {
	message_type_t type;
    double x;
    double y;
    double z;
} global_fix_t;

typedef struct _eo_ir_video {
	message_type_t type;
	double data[16];
} eo_ir_video_t;

typedef struct _eo_ir_track {
	message_type_t type;
	track_data_t track;
} eo_ir_track_t;

typedef struct _pnt_src {
	message_type_t type;
	global_fix_t position_fix;
} pnt_position_t;

typedef struct _pnt_src_time {
	message_type_t type;
	long time;
} pnt_time_t;

#endif /*_TARCK_H_*/
