#ifndef _PRODUCE_H
#define _PRODUCE_H

extern pnt_position_t pnt_src_data;
extern long timestamp;
extern global_fix_t global_fix;
extern rf_track_t rf_track;
extern global_fix_t position_fix;
extern track_data_t target_track_pos_velocity;
extern track_data_t target_track;
extern rf_mti_t rf_mti;
extern eo_ir_video_t eo_ir_video;
extern rf_sensor_t rf_sensor_data;
extern eo_ir_track_t eo_ir_track;
extern pnt_position_t pnt_position_data;

long produce_time();
track_data_t *produce_own_ship_track(global_fix_t *position_fix);
rf_mti_t *produce_rf_mti();
rf_track_t *produce_rf_track();
eo_ir_video_t *produce_eo_ir_video();
global_fix_t *produce_position_fix();
global_fix_t *produce_global_fix();
rf_sensor_t *produce_rf_sensor();
eo_ir_track_t *produce_eo_ir_track();
track_data_t *produce_target_track_pos_velocity();
track_data_t *produce_target_track();
pnt_position_t *produce_pnt_position_data();

#endif
