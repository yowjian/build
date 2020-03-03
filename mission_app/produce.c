#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "track.h"

pnt_position_t pnt_src_data = { .position_fix = { .x = 100, .y = 200, .z = 300}, .time = 1980 };
long timestamp;
global_fix_t global_fix;
rf_track_t rf_track;
global_fix_t position_fix;
track_data_t target_track_pos_velocity;
track_data_t target_track;
rf_mti_t rf_mti;
eo_ir_video_t eo_ir_video;
rf_sensor_t rf_sensor_data;
eo_ir_track_t eo_ir_track;
pnt_position_t pnt_position_data;

long produce_time()
{
	timestamp = time(NULL);
	return timestamp;
}

track_data_t *produce_target_track()
{
	target_track.lat = 32.673169;
	target_track.lon = -117.644569;
	target_track.hae = 1000;
	target_track.speed = 1001;
	target_track.course = 1002;
	time(NULL);

	return &target_track;
}

rf_mti_t *produce_rf_mti()
{
	rf_mti.mti = 1.0;

	return &rf_mti;
}

rf_track_t *produce_rf_track()
{
	rf_track.track.lat = 44.123456;
	rf_track.track.lon = -123.345678;
	rf_track.track.hae = 1010;
	rf_track.track.speed = 1011;
	rf_track.track.course = 1012;
	time(NULL);

	return &rf_track;
}

eo_ir_video_t *produce_eo_ir_video()
{
	snprintf((char *) eo_ir_video.data, sizeof(eo_ir_video_t), "a");

	return &eo_ir_video;
}

global_fix_t *produce_position_fix() //eo_ir_track_t *track)
{
	position_fix.x = 300;
	position_fix.y = 301;
	position_fix.z = 302;

	return &position_fix;
}

global_fix_t *produce_global_fix() //eo_ir_track_t *track)
{
	global_fix.x = 400;
	global_fix.y = 401;
	global_fix.z = 402;

	return &global_fix;
}

rf_sensor_t *produce_rf_sensor()
{
	rf_sensor_data.azimuth = 123;
	rf_sensor_data.range = 456;

	return &rf_sensor_data;
}

eo_ir_track_t *produce_eo_ir_track() //track_data_t *target_track, eo_ir_video_t *eo_ir)
{
	eo_ir_track.track.lat = 40;
	eo_ir_track.track.lon = -207;
	eo_ir_track.track.hae = 2100;
	eo_ir_track.track.speed = 2101;
	eo_ir_track.track.course = 2102;
	eo_ir_track.track.timestamp = time(NULL);

	return &eo_ir_track;
}

track_data_t *produce_target_track_pos_velocity()
{
	target_track_pos_velocity.lat = 30;
	target_track_pos_velocity.lon = -107;
	target_track_pos_velocity.hae = 2000;
	target_track_pos_velocity.speed = 2001;
	target_track_pos_velocity.course = 2002;
	target_track_pos_velocity.timestamp = time(NULL);

	return &target_track_pos_velocity;
}

pnt_position_t *produce_pnt_position_data()
{
	pnt_position_data.position_fix.x = 500;
	pnt_position_data.position_fix.y = 501;
	pnt_position_data.position_fix.z = 502;

	return &pnt_position_data;
}
