#ifndef _SEND_RECV_H
#define _SEND_RECV_H

#include <netinet/in.h>

#include "track.h"

typedef struct _UdpEndPoint {
	char name[64];
    int sock;
    struct sockaddr_in dst;             // destination address
    struct _UdpEndPoint *next;
} UdpEndPoint;

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
UdpEndPoint *create_udp_endpoint(char *name, char *local_ip, int local_port); //, char *remote_ip, int remote_port);
void init_fd();
UdpEndPoint *findEndpoint(char *name);
void udp_send(UdpEndPoint *sender, UdpEndPoint *recipient, char *data, int data_len);
void udp_recv(UdpEndPoint *uep, char *buf, int buf_len);

#endif
