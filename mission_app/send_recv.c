#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "track.h"
#include "produce.h"

void output(char *msg, char *data)
{
	printf("%s\n", msg);
}

void write_gaps(char *msg, char *data)
{
	printf("%s\n", msg);
	// TODO: send data
}

void read_gaps(char *buf)
{

}

void write_local(char *msg, char *data)
{
	printf("%s\n", msg);
}

rf_sensor_t *read_rf_sensor()
{
	rf_sensor_t *rf = malloc(sizeof(rf_sensor_t));
	rf->azimuth = 130;
	rf->range = 45;

	return rf;
}

long recv_timestamp()
{
	return timestamp;
}

track_data_t *recv_target_track()
{
	return &target_track;
}

track_data_t *recv_target_track_pos_velocity()
{
	return &target_track_pos_velocity;
}

rf_mti_t *recv_rf_mti()
{
	return &rf_mti;
}

rf_track_t *recv_rf_track()
{
	return &rf_track;
}

eo_ir_video_t *recv_eo_ir_video()
{
	return &eo_ir_video;
}

global_fix_t *recv_position_fix()
{
	return &position_fix;
}

global_fix_t *recv_global_fix()
{
	return &global_fix;
}

rf_sensor_t *recv_rf_sensor()
{
	return &rf_sensor_data;
}

eo_ir_track_t *recv_eo_ir_track()
{
	return &eo_ir_track;
}

pnt_position_t *recv_pnt_position_data()
{
	return &pnt_position_data;
}
