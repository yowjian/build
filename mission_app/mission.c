#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <getopt.h>
#include <unistd.h>

#include "track.h"
#include "produce.h"
#include "send_recv.h"
#include "log.h"

#define PRODUCE_DELAY 5

#define PNT_SRC 			"pnt_src"
#define POSITION_PROCESSING "position_processing"
#define TIME_PROCESSING 	"time_processing"
#define TARGET_LOC		 	"target_loc"
#define TRACKING_EO_IR 		"tracking_eo_ir"
#define EO_OR_SENSOR 		"eo_ir_sensor"
#define RF_SENSOR 			"rf_sensor"
#define TRACKING_RF_MTI 	"tracking_rf_mti"
#define OWN_SHIP_LOC 		"own_ship_loc"
#define CORRELATION 		"correlation"

#define OK 0
#define NOTOK -1

#pragma cle def GREEN_1 {"level":"green",\
  "cdf": [\
    {"remotelevel":"==orange", \
     "direction": "egress", \
     "guardhint": { "oneway": "true"}}\
  ] }}

#pragma cle def ORANGE_1 {"level":"orange",\
  "cdf": [\
    {"remotelevel":"==green", \
     "direction": "egress", \
     "guardhint": { "oneway": "true"}}\
  ] }

void die(char *s)
{
	perror(s);
	exit(1);
}

void* correlation(void *arg)
{
	global_fix_t *global_fix = recv_global_fix();
	mc_log(LOG_INFO, "correlation: recv global fix", (char *) global_fix);

	rf_track_t *rf_track = recv_rf_track();
	mc_log(LOG_INFO, "correlation: recv RF Track", (char *) rf_track);

	return NULL;
}

void *own_ship_loc(void *arg)
{
	global_fix_t *position_fix = recv_position_fix();
	mc_log(LOG_INFO, "own_ship_loc: recv position fix", (char *) position_fix);

#pragma cle begin ORANGE_1
	track_data_t *target_track = produce_target_track_pos_velocity(position_fix);
#pragma cle end ORANGE_1
	write_gaps("own_ship_loc: send target track (pos, velocity)", (char *) target_track);

	return NULL;
}

void *tracking_rf_mti(void *arg)
{
	track_data_t *target_track = recv_target_track();
	mc_log(LOG_INFO, "tracking: recv target track", (char *) target_track);

	rf_mti_t *rf_mti = recv_rf_mti();

	rf_track_t *tf_track = produce_rf_track(target_track, rf_mti);
	write_local("tracking: send RF Track", (char *) tf_track);

	return NULL;
}

void *rf_sensor(void *arg)
{
	rf_mti_t *rf_mti = produce_rf_mti();
	write_local("rf_sensor: send MTI", (char *) rf_mti);

#pragma cle begin GREEN_1
	rf_sensor_t *rf_sensor = produce_rf_sensor();
#pragma cle end GREEN_1
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
	UdpEndPoint *me = (UdpEndPoint *) arg;

	UdpEndPoint *position_processing = findEndpoint(POSITION_PROCESSING);
	UdpEndPoint *time_processing = findEndpoint(TIME_PROCESSING);

	while (1) {
		pnt_position_t *pnt_position_data = produce_pnt_position_data();
		udp_send(me, position_processing, (char *) pnt_position_data, sizeof(pnt_position_t));

		long timestamp = produce_time();
		udp_send(me, time_processing, (char *) &timestamp, sizeof(long));

		sleep(PRODUCE_DELAY);
	}
}

void *position_processing(void *arg)
{
	UdpEndPoint *me = (UdpEndPoint *) arg;
	UdpEndPoint *own_ship_loc = findEndpoint(OWN_SHIP_LOC);

	pnt_position_t pnt_position_data;

	while (1) {
		udp_recv(me, (char *) &pnt_position_data, sizeof(pnt_position_t));

#pragma cle begin GREEN_1
		global_fix_t *position_fix = produce_position_fix();
#pragma cle end GREEN_1

		udp_send(me, own_ship_loc, (char *) position_fix, sizeof(global_fix_t));
	}
}

void *time_processing(void *arg)
{
	UdpEndPoint *me = (UdpEndPoint *) arg;
	UdpEndPoint *target_loc = findEndpoint(TARGET_LOC);

	long timestamp;

	while (1) {
		udp_recv(me, (char *) &timestamp, sizeof(long));
		udp_send(me, target_loc, (char *) &timestamp, sizeof(long));
	}
}

void *tracking_eo_ir(void *arg)
{
	eo_ir_track_t *eo_ir_track = recv_eo_ir_track();
	mc_log(LOG_INFO, "tracking_eo_ir: recv EO/IR Track", (char *) eo_ir_track);

#pragma cle begin GREEN_1
	global_fix_t *global_fix = produce_global_fix();
#pragma cle end GREEN_1
	write_gaps("tracking_eo_ir: send Global Fix", (char *) global_fix);

	return NULL;
}

void *target_loc(void *arg)
{
	long timestamp = recv_timestamp();
	mc_log(LOG_INFO, "target_loc: recv timestamp", (char *) &timestamp);

	eo_ir_video_t *eo_ir_video = recv_eo_ir_video();
	mc_log(LOG_INFO, "target_loc: recv EO/IR video", (char *) eo_ir_video);

	track_data_t *target_track_pos_velocity = recv_target_track_pos_velocity();
	mc_log(LOG_INFO, "target_loc: recv target  (pos, velocity)", (char *) target_track_pos_velocity);

	rf_sensor_t *rf_sensor = recv_rf_sensor();
	mc_log(LOG_INFO, "target_loc: recv Azimuth/range", (char *) rf_sensor);

	eo_ir_track_t *eo_ir_track = produce_eo_ir_track();
	write_local("target_loc: send EO/IR Track", (char *) eo_ir_track);

#pragma cle begin GREEN_1
	track_data_t *target_track = produce_target_track_pos_velocity();
#pragma cle begin GREEN_1
	write_gaps("target_loc: send target track", (char *) target_track);

	return NULL;
}

void start_thread(void *(*func)(void *), char *name)
{
	UdpEndPoint *uep = findEndpoint(name);

    pthread_t thread;
    int ret = pthread_create(&thread, 0, func, uep);
    if (ret != 0) {
    	char buf[128];
    	sprintf(buf, "thread %s pthread_create fail", name);
    	die(buf);
    }
}

static void read_config_file(char* config_filename)
{
    FILE *fp;
    const int LINE_SIZE = 128;
    char buf[LINE_SIZE];

    if ((fp = fopen(config_filename, "r")) == NULL) {
        mc_log(LOG_ALERT, "Failed to open config file %s\n", config_filename);
        exit(EXIT_FAILURE);
    }

    char name[64], local_ip[32]; //, remote_ip[32];
    int local_port; //, remote_port;
    while (fgets(buf, LINE_SIZE, fp) != NULL) {
        if (buf[0] == '#' || strlen(buf) < 4) {
            continue;
        }

        int cnt = sscanf(buf, "%s %s %d\n", name, local_ip, &local_port); //, remote_ip, &remote_port);
        if (cnt < 3) {
        	mc_log(LOG_ERR, "invalid config line");
        	continue;
        }
        create_udp_endpoint(name, local_ip, local_port); //, remote_ip, remote_port);
    }
}

static void print_usage()
{
    printf("Options:\n");
    printf("  -f     \t config file\n");
    printf("  -h     \t print this message and exit\n");

    exit(0);
}

static void parse_cmdline(int argc, char *argv[])
{
    int c;

    struct option long_options[] = {
        {"file",    required_argument, 0, 'f'},
        {"help",    no_argument,       0, 'h'},
        {0, 0, 0, 0}
    };

    int option_index = 0;
    int specified = 0;
    while ((c = getopt_long(argc, argv, "hf:", long_options, &option_index)) != -1) {
        switch (c) {
        case 'f':
            read_config_file(optarg);
            specified = 1;
            break;
        case 'h':
            print_usage();
            break;
        default:
            abort ();
        }
    }
    if (!specified)
    	read_config_file("mapp.conf");
}

int main(int argc, char * argv[])
{
    mc_setup_log();
    init_fd();
    parse_cmdline(argc, argv);

	start_thread(pnt_src, "pnt_src");
	start_thread(eo_ir_sensor, "eo_ir_sensor");
	start_thread(rf_sensor, "rf_sensor");

	start_thread(time_processing, "time_processing");  			// depends on pnt_src
	start_thread(position_processing, "position_processing");  	// depends on pnt_src
	start_thread(own_ship_loc, "own_ship_loc");					// depends on position_processing

	start_thread(target_loc, "target_loc");   // depends on rf_sensor, eo_ir_sensor, time_processing, own_sihp_loc

	start_thread(tracking_rf_mti, "tracking_rf_mti");  	// depends on rf_sensor, target_loc
	start_thread(tracking_eo_ir, "tracking_eo_ir");		// depends on target_loc
	start_thread(correlation, "correlation"); 			// depends on tracking_rf_mti, tracking_eo_ir

	sleep(1000);
}
