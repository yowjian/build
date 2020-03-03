#ifndef _SEND_RECV_H
#define _SEND_RECV_H

#include "track.h"

void output(char *msg, char *data);
void write_gaps(char *msg, char *data);
void write_local(char *msg, char *data);
rf_sensor_t *read_rf_sensor();
long recv_timestamp();
track_data_t *recv_target_track();
track_data_t *recv_target_track_pos_velocity();
rf_mti_t *recv_rf_mti();
rf_track_t *recv_rf_track();
eo_ir_video_t *recv_eo_ir_video();
global_fix_t *recv_position_fix();
global_fix_t *recv_global_fix();
rf_sensor_t *recv_rf_sensor();
eo_ir_track_t *recv_eo_ir_track();
pnt_position_t *recv_pnt_position_data();

#endif
