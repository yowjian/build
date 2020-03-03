#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "imaging.h"
#include "gps_lib.h"
#include "targeting.h"
#include "track.h"

#define OK 0
#define NOTOK -1

pnt_src_t pnt_src = { .position_fix = { .x = 100, .y = 200, .z = 300}, .time = 1980 };

/*
#pragma cle def PURPLE_1 {"level":"purple"}

#pragma cle def ORANGE_1 {"level":"orange",\
  "cdf": [\
    {"remotelevel":"==purple", \
     "direction": "egress", \
     "guardhint": { "oneway": "true"}}\
  ] }
*/

gps_data_t * receive_gps() {
  return get_gps_data();
}



targeting_data_t * receive_targeting() {
  targeting_data_t * t = (targeting_data_t *)malloc(sizeof(targeting_data_t));
  t->range = 10;
  t->heading = 20;
  t->width = 800;
  t->height = 600;
  strcpy(t->name, "Speedboat Alpha");
  return t;
}

int receive_image(image_t * i) {
  char * filename = "boats.jpg";
  *i = filename;
  char cmd[200];
  snprintf(cmd, 200, "display -resize 25%% %s", filename);
  system(cmd);
  return OK;
}

int combine_and_display_data(gps_data_t * g, targeting_data_t * t, image_t i) {
  //something to combine the data
  //and display image
  printf("Target '%s' at time %.24s, coordinates (%f %f), size is (%d, %d) image: '%s'\n",
	 t->name, ctime(&(g->timestamp)), g->lat, g->lon, t->width, t->height, i);
  char cmd[1024];
  char * final_img_name = "/tmp/gaps_img_target.jpg";
  snprintf(cmd, 1024, "convert %s -crop %dx%d+%d+%d -pointsize 20 -fill yellow "
	   "-draw 'text %d,%d \"Target metadata: %s\"' -draw 'text %d,%d \"Local time: %.24s\"' -draw 'text %d,%d \"Coordinates: %f %f\"' %s",
	   i, t->width, t->height, g->x, g->y,
	   g->x + ((int) (t->width * 0.1)), g->y + ((int) (t->height * 0.8)), t->name,
	   g->x + ((int) (t->width * 0.1)), g->y + ((int) (t->height * 0.85)), ctime(&(g->timestamp)),
	   g->x + ((int) (t->width * 0.1)), g->y + ((int) (t->height * 0.9)), g->lat, g->lon,
	   final_img_name);
  //printf("%s\n", cmd);
  system(cmd);
  snprintf(cmd, 1024, "display %s", final_img_name);
  system(cmd);
  return OK;
}

void write_gaps(char *msg, char *data)
{
	printf("%s\n", msg);
	// TODO: send data
}

track_data_t *recv_own_ship_track(global_fix_t *position_fix)
{
	track_data_t *track = malloc(sizeof(track_data_t));
	track->lat = 32.673169;
	track->lon = -117.644569;
	track->hae = 1000;
	track->speed = 1001;
	track->course = 1002;
	time(&track->timestamp);

	return track;
}

long read_time()
{
	return time(NULL);
}

rf_sensor_t *read_rf_sensor()
{
	rf_sensor_t *rf = malloc(sizeof(rf_sensor_t));
	rf->azimuth = 130;
	rf->range = 45;

	write_gaps("send Azimuth/range", (char *) rf);

	return rf;
}

eo_ir_t *read_eo_ir()
{
	eo_ir_t *eo_ir = malloc(sizeof(eo_ir_t));
	sprintf((char *)&eo_ir->data, "a");

	printf("send EO/IR Video\n");

	return eo_ir;
}

global_fix_t *produce_target_global_fix(eo_ir_track_t *track)
{
	global_fix_t *fix = malloc(sizeof(global_fix_t));
	fix->x = 300;
	fix->y = 301;
	fix->z = 302;

	return fix;
}

eo_ir_track_t *produce_eo_ir_track(track_data_t *target_track, eo_ir_t *eo_ir)
{
	eo_ir_track_t *eo_ir_track = malloc(sizeof(eo_ir_track_t));
	strncpy((char *)&eo_ir_track->track, (char *)target_track, sizeof(eo_ir_track));

	return eo_ir_track;
}

track_data_t *produce_target_track(long time, rf_sensor_t *rf_sensor, track_data_t *own_ship_track)
{
	track_data_t *track = malloc(sizeof(track_data_t));
	track->lat = 30;
	track->lon = -107;
	track->hae = 2000;
	track->speed = 2001;
	track->course = 2002;
	track->timestamp = time;

	return track;
}

void write_target_track(track_data_t *track)
{
}

void write_target_global_fix(global_fix_t *target_global_fix)
{
}

global_fix_t *recv_position_fix()
{
	time(&pnt_src.time);

	printf("get_position_fix: time=%ld, x=%6.2f, y=%6.2f, z=%6.2f\n",
			pnt_src.time, pnt_src.position_fix.x, pnt_src.position_fix.y, pnt_src.position_fix.z);

	return &pnt_src.position_fix;
}

void target_loc_processing()
{
	global_fix_t *position_fix = recv_position_fix();
	write_gaps("send position fix", (char *) position_fix);
	long time = read_time();

	rf_sensor_t *rf_sensor;
	eo_ir_t *eo_ir;

	track_data_t *own_ship_track = recv_own_ship_track(position_fix);
	write_gaps("send own ship track", (char *) own_ship_track);

	rf_sensor = read_rf_sensor();  // azimuth and range
	eo_ir = read_eo_ir();

	// processing to produce target_track
	track_data_t *target_track = produce_target_track(time, rf_sensor, own_ship_track);
	write_gaps("send target track", (char *) target_track);

	// processing to produce eo_ir track
	eo_ir_track_t *eo_ir_track = produce_eo_ir_track(target_track, eo_ir);
	global_fix_t *target_global_fix = produce_target_global_fix(eo_ir_track);
	write_gaps("send target global fix", (char *) target_global_fix);
}

int main(int argc, char * argv[]) {
	target_loc_processing();
}
