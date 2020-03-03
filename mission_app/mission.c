#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "track.h"
#include "produce.h"
#include "send_recv.h"

#define OK 0
#define NOTOK -1

/*
#pragma cle def PURPLE_1 {"level":"purple"}

#pragma cle def ORANGE_1 {"level":"orange",\
  "cdf": [\
    {"remotelevel":"==purple", \
     "direction": "egress", \
     "guardhint": { "oneway": "true"}}\
  ] }
*/

void* correlation(void *arg)
{
	global_fix_t *global_fix = recv_global_fix();
	output("correlation: recv global fix", (char *) global_fix);

	rf_track_t *rf_track = recv_rf_track();
	output("correlation: recv RF Track", (char *) rf_track);

	return NULL;
}

void *own_ship_loc(void *arg)
{
	global_fix_t *position_fix = recv_position_fix();
	output("own_ship_loc: recv position fix", (char *) position_fix);

	track_data_t *target_track = produce_target_track_pos_velocity(position_fix);
	write_gaps("own_ship_loc: send target track (pos, velocity)", (char *) target_track);

	return NULL;
}

void *tracking_rf_mti(void *arg)
{
	track_data_t *target_track = recv_target_track();
	output("tracking: recv target track", (char *) target_track);

	rf_mti_t *rf_mti = recv_rf_mti();

	rf_track_t *tf_track = produce_rf_track(target_track, rf_mti);
	write_local("tracking: send RF Track", (char *) tf_track);

	return NULL;
}

void *rf_sensor(void *arg)
{
	rf_mti_t *rf_mti = produce_rf_mti();
	write_local("rf_sensor: send MTI", (char *) rf_mti);

	rf_sensor_t *rf_sensor = produce_rf_sensor();
	write_gaps("rf_sensor: send Azimuth/range", (char *) rf_sensor);

	return NULL;
}

void *eo_ir_sensor(void *arg)
{
	eo_ir_video_t *eo_ir_video = produce_eo_ir_video();
	write_local("eo_ir_sensor: send EO/IR video", (char *) eo_ir_video);

	return NULL;
}

void *pnt_src(void *arg)
{
	pnt_position_t *pnt_position_data = produce_pnt_position_data();
	write_local("pnt_src: send PNT position data", (char *) pnt_position_data);

	long timestamp = produce_time();
	write_local("pnt_src: send PNT timestamp", (char *) &timestamp);

	return NULL;
}

void *position_processing(void *arg)
{
	pnt_position_t *pnt_position_data = recv_pnt_position_data();
	output("position_processing: recv PNT position data", (char *) pnt_position_data);

	global_fix_t *position_fix = produce_position_fix();
	write_gaps("position_processing: send position fix", (char *) position_fix);

	return NULL;
}

void *time_processing(void *arg)
{
	long timestamp = recv_timestamp();
	output("time_processing: recv timestamp", (char *) &timestamp);

	write_local("time_processing: send Time", (char *) &timestamp);

	return NULL;
}

void *tracking_eo_ir(void *arg)
{
	eo_ir_track_t *eo_ir_track = recv_eo_ir_track();
	output("tracking_eo_ir: recv EO/IR Track", (char *) eo_ir_track);


	global_fix_t *global_fix = produce_global_fix();
	write_gaps("tracking_eo_ir: send Global Fix", (char *) global_fix);

	return NULL;
}

void *target_loc(void *arg)
{
	long timestamp = recv_timestamp();
	output("target_loc: recv timestamp", (char *) &timestamp);

	eo_ir_video_t *eo_ir_video = recv_eo_ir_video();
	output("target_loc: recv EO/IR video", (char *) eo_ir_video);

	track_data_t *target_track_pos_velocity = recv_target_track_pos_velocity();
	output("target_loc: recv target  (pos, velocity)", (char *) target_track_pos_velocity);

	rf_sensor_t *rf_sensor = recv_rf_sensor();
	output("target_loc: recv Azimuth/range", (char *) rf_sensor);

	eo_ir_track_t *eo_ir_track = produce_eo_ir_track();
	write_local("target_loc: send EO/IR Track", (char *) eo_ir_track);


	track_data_t *target_track = produce_target_track_pos_velocity();
	write_gaps("target_loc: send target track", (char *) target_track);

	return NULL;
}

int main(int argc, char * argv[])
{
	pnt_src(NULL);
	eo_ir_sensor(NULL);
	rf_sensor(NULL);

	time_processing(NULL);  	// depends on pnt_src
	position_processing(NULL);	// depends on pnt_src
	own_ship_loc(NULL);  		// depends on position_processing

	target_loc(NULL);			// depends on rf_sensor, eo_ir_sensor, time_processing, own_sihp_loc

	tracking_rf_mti(NULL);		// depends on rf_sensor, target_loc
	tracking_eo_ir(NULL);		// depends on target_loc

	correlation(NULL);			// depends on tracking_rf_mti, tracking_eo_ir
}
