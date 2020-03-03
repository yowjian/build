#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <errno.h>

#include "track.h"
#include "produce.h"
#include "send_recv.h"
#include "log.h"

int epoll_fd;
UdpEndPoint *all_endpoints = NULL;

void init_fd()
{
    epoll_fd = epoll_create1(0);
}

/**
 * Add the file descriptor to the master.
 */
void add_fd(int fd)
{
    struct epoll_event event;

    event.data.fd = fd;
    event.events = EPOLLIN;
    int s = epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd, &event);
    if (s == -1) {
        mc_log(LOG_ERR, "add_fd: could not add fd: %d, %s", fd, strerror(errno));
    }
}

UdpEndPoint *findEndpoint(char *name)
{
	UdpEndPoint *uep = all_endpoints;

	while (uep != NULL) {
		if (!strcmp(uep->name, name))
			return uep;
		uep = uep->next;
	}

	mc_log(LOG_EMERG, "%s: endpoint not found", name);
	// exit(1);

	return 0;
}

void udp_send(UdpEndPoint *sender, UdpEndPoint *recipient, char *data, int data_len)
{
	if (sender == NULL || recipient == NULL) {
		mc_log(LOG_ERR, "null endpoint %x -> %x , data not sent", sender, recipient);
		return;
	}

	int sent_bytes = sendto(sender->sock, data, data_len,
						    0, (struct sockaddr *)&recipient->dst, sizeof(recipient->dst));
    if (sent_bytes == -1) {
        mc_log(LOG_ERR, "failed to send from %s to %s", sender->name, recipient->name, strerror(errno));
    }
    else {
        mc_log(LOG_INFO, "sent %4d bytes (%s -> %s)", sent_bytes, sender->name, recipient->name);
    }
}

void udp_recv(UdpEndPoint *uep, char *buf, int buf_len)
{
    struct sockaddr_in si_other;
    int recv_len;
    socklen_t slen = sizeof(si_other);

    if ((recv_len = recvfrom(uep->sock, buf, buf_len, 0, (struct sockaddr *) &si_other, &slen)) == -1) {
        mc_log(LOG_ERR, "%s failed to receive: %s", uep->name, strerror(errno));
        return;
    }
    //buf[recv_len] = '\0';

    mc_log(LOG_INFO, "recv %4d bytes -> %s",  recv_len, uep->name);
}

UdpEndPoint *create_udp_endpoint(char *name, char *local_ip, int local_port) //, char *remote_ip, int remote_port)
{
    struct sockaddr_in si_me;
    int sock;

    if ((sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
        mc_log(LOG_ERR, "cannot create socket: %s", local_ip);
        return NULL;
    }

    memset((char *) &si_me, 0, sizeof(si_me));
    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(local_port);
    if (local_ip == NULL)
        si_me.sin_addr.s_addr = htonl(INADDR_ANY);
    else {
        if (inet_aton(local_ip, &si_me.sin_addr) == 0) {
            mc_log(LOG_ERR, "invalid address: %s", local_ip);
            close(sock);
            return NULL;
        }
    }

    if (bind(sock, (struct sockaddr*) &si_me, sizeof(si_me)) == -1) {
        mc_log(LOG_ERR, "cannot bind: %s", local_ip);
        //TODO: Uncomment the lines below
        //close(sock);
        //return NULL;
    }

    UdpEndPoint *endpoint = malloc(sizeof(UdpEndPoint));
    strcpy(endpoint->name, name);
    endpoint->sock = sock;
    endpoint->next = all_endpoints;
    all_endpoints = endpoint;

	struct sockaddr_in *sockaddr = &endpoint->dst;
	memset((char *) sockaddr, 0, sizeof(*sockaddr));
	sockaddr->sin_family = AF_INET;
	sockaddr->sin_port = htons(local_port);

	if (inet_aton(local_ip, &sockaddr->sin_addr) == 0) {
		mc_log(LOG_ERR, "invalid address: %s", local_ip);
		close(sock);
		return NULL;
	}

    add_fd(sock);

    mc_log(LOG_INFO, "UDP endpoint created: %s:%d", local_ip, local_port); //, remote_ip, remote_port);

    return endpoint;
}

void write_gaps(char *msg, char *data)
{
	mc_log(LOG_INFO, "%s", msg);
	// TODO: send data
}

void read_gaps(char *buf)
{

}

void write_local(char *msg, char *data)
{
	mc_log(LOG_DEBUG, "%s", msg);
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
