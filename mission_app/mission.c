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
#define EO_IR_SENSOR 		"eo_ir_sensor"
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
    UdpEndPoint *me = (UdpEndPoint *) arg;

    global_fix_t global_fix;   // from tracking_eo_ir
    rf_track_t rf_track;       // from tracking_rf_mti

    int larger = sizeof(global_fix_t) > sizeof(rf_track);
    char *buf = larger ? (char *) &global_fix : (char *) &rf_track;
    int buf_size = larger ? sizeof(global_fix_t) : sizeof(rf_track);

    global_fix_t *data_ptr = (global_fix_t *) buf;

    while (1) {
        udp_recv(me, (char *) buf, buf_size);

        if (data_ptr->type == TYPE_GLOBAL_FIX) {
        	mc_log(LOG_DEBUG, "%s receives global fix", __FUNCTION__);
        }
        else if (data_ptr->type == TYPE_RF_TRACK) {
        	mc_log(LOG_DEBUG, "%s receives rf track", __FUNCTION__);
        }
        else {
        	mc_log(LOG_ERR, "%s receives data type: %d", __FUNCTION__, data_ptr->type);
        }
    }
}

void *own_ship_loc(void *arg)
{
    UdpEndPoint *me = (UdpEndPoint *) arg;
    UdpEndPoint *target_loc = findEndpoint(TARGET_LOC);

    global_fix_t position_fix;

    while (1) {
        udp_recv(me, (char *) &position_fix, sizeof(global_fix_t));

#pragma cle begin ORANGE_1
        track_data_t *target_track = produce_target_track_pos_velocity(position_fix);
#pragma cle end ORANGE_1
        udp_send(me, target_loc, (char *) target_track, sizeof(track_data_t));
    }
}

void *tracking_rf_mti(void *arg)
{
    UdpEndPoint *me = (UdpEndPoint *) arg;
    UdpEndPoint *correlation = findEndpoint(CORRELATION);

    track_data_t target_track;
    rf_mti_t rf_mti;

    while (1) {
        udp_recv(me, (char *) &target_track, sizeof(track_data_t));
        udp_recv(me, (char *) &rf_mti, sizeof(rf_mti_t));

        rf_track_t *rf_track = produce_rf_track(target_track, rf_mti);
        udp_send(me, correlation, (char *) rf_track, sizeof(rf_track_t));
    }
}

void *rf_sensor(void *arg)
{
    UdpEndPoint *me = (UdpEndPoint *) arg;
    UdpEndPoint *tracking_rf_mti = findEndpoint(TRACKING_RF_MTI);
    UdpEndPoint *target_loc = findEndpoint(TARGET_LOC);

    while (1) {
        rf_mti_t *rf_mti = produce_rf_mti();
        udp_send(me, tracking_rf_mti, (char *) rf_mti, sizeof(rf_mti_t));

#pragma cle begin GREEN_1
        rf_sensor_t *rf_sensor = produce_rf_sensor();
#pragma cle end GREEN_1

        udp_send(me, target_loc, (char *) rf_sensor, sizeof(rf_sensor_t));

        sleep(PRODUCE_DELAY);
    }
}

void *eo_ir_sensor(void *arg)
{
    UdpEndPoint *me = (UdpEndPoint *) arg;
    UdpEndPoint *target_loc = findEndpoint(TARGET_LOC);

    while (1) {
        eo_ir_video_t *eo_ir_video = produce_eo_ir_video();
        udp_send(me, target_loc, (char *) eo_ir_video, sizeof(eo_ir_video_t));

        sleep(PRODUCE_DELAY);
    }
}

void *pnt_src(void *arg)
{
	UdpEndPoint *me = (UdpEndPoint *) arg;

	UdpEndPoint *position_processing = findEndpoint(POSITION_PROCESSING);
	UdpEndPoint *time_processing = findEndpoint(TIME_PROCESSING);

	while (1) {
		pnt_position_t *pnt_position_data = produce_pnt_position_data();
		udp_send(me, position_processing, (char *) pnt_position_data, sizeof(pnt_position_t));

		pnt_time_t *timestamp = produce_pnt_time();
		udp_send(me, time_processing, (char *) &timestamp, sizeof(pnt_time_t));

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
    UdpEndPoint *me = (UdpEndPoint *) arg;
    UdpEndPoint *correlation = findEndpoint(CORRELATION);

    eo_ir_track_t eo_ir_track;

    while (1) {
        udp_recv(me, (char *) &eo_ir_track, sizeof(eo_ir_track_t));

        if (eo_ir_track.type == TYPE_EO_IR_TRACK) {
        	mc_log(LOG_DEBUG, "%s receives eo_ir_track", __FUNCTION__);
        }
        else {
        	mc_log(LOG_ERR, "%s receives data type: %d", __FUNCTION__, eo_ir_track.type);
        	continue;
        }

#pragma cle begin GREEN_1
        global_fix_t *global_fix = produce_global_fix();
#pragma cle end GREEN_1
        udp_send(me, correlation, (char *) global_fix, sizeof(global_fix_t));
    }
}

void *target_loc(void *arg)
{
    UdpEndPoint *me = (UdpEndPoint *) arg;
    UdpEndPoint *tracking_rf_mti = findEndpoint(TRACKING_RF_MTI);
    UdpEndPoint *tracking_eo_ir = findEndpoint(TRACKING_EO_IR);

    long timestamp;
    eo_ir_video_t eo_ir_video;
    track_data_t target_track_pos_velocity;
    rf_sensor_t rf_sensor;

    while (1) {
        udp_recv(me, (char *) &timestamp, sizeof(long));
        udp_recv(me, (char *) &eo_ir_video, sizeof(eo_ir_video_t));
        udp_recv(me, (char *) &target_track_pos_velocity, sizeof(track_data_t));
        udp_recv(me, (char *) &rf_sensor, sizeof(rf_sensor_t));

        eo_ir_track_t *eo_ir_track = produce_eo_ir_track();
        udp_send(me, tracking_eo_ir, (char *) eo_ir_track, sizeof(eo_ir_track_t));

#pragma cle begin GREEN_1
        track_data_t *target_track = produce_target_track();
#pragma cle begin GREEN_1
        udp_send(me, tracking_rf_mti, (char *) &target_track, sizeof(track_data_t));
    }
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

	start_thread(pnt_src, PNT_SRC);
	start_thread(eo_ir_sensor, EO_IR_SENSOR);
	start_thread(rf_sensor, RF_SENSOR);

	start_thread(time_processing, TIME_PROCESSING);  			// depends on pnt_src
	start_thread(position_processing, POSITION_PROCESSING);  	// depends on pnt_src
	start_thread(own_ship_loc, OWN_SHIP_LOC);					// depends on position_processing

	start_thread(target_loc, TARGET_LOC);   // depends on rf_sensor, eo_ir_sensor, time_processing, own_sihp_loc

	start_thread(tracking_rf_mti, TRACKING_RF_MTI);  	// depends on rf_sensor, target_loc
	start_thread(tracking_eo_ir, TRACKING_EO_IR);		// depends on target_loc
	start_thread(correlation, CORRELATION); 			// depends on tracking_rf_mti, tracking_eo_ir

	sleep(1000);
}
