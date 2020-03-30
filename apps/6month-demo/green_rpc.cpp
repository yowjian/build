#include <iostream>

#include "ownship.h"

#include "hal_xdcomms.h"
#include "hal_gma.h"

void OwnShipShadow::receive()
{
    gaps_tag t_tag;
    uint32_t t_mux = 2, t_sec = 2, type = DATA_TYP_POSITION;

    tag_write(&t_tag, t_mux, t_sec, type);
    void *socket = xdc_socket(t_tag);

    Position position(0, 0, 0);
    position_datatype pos;

    while (1) {
        xdc_blocking_recv(socket, &pos, &t_tag);
        position._x = pos.x;
        position._y = pos.y;
        position._z = pos.z;

        setPosition(position);
        notify();
    }

    xdc_close(socket, NULL); // TODO
}

void RfSensorShadow::receive()
{
    gaps_tag t_tag;
    uint32_t t_mux = 2, t_sec = 2, type = DATA_TYP_DISTANCE;

    tag_write(&t_tag, t_mux, t_sec, type);
    void *socket = xdc_socket(t_tag);

    Distance distance(0, 0, 0);
    distance_datatype dis;

    while (1) {
        xdc_blocking_recv(socket, &dis, &t_tag);
        distance._dx = dis.x;
        distance._dy = dis.y;
        distance._dz = dis.z;

        setDistance(distance);
        notify();
    }

    xdc_close(socket, NULL); // TODO
}

void hal_init()
{
  xdc_set_out((char *)"ipc:///tmp/halpubbwgreen");
  xdc_set_in((char *)"ipc:///tmp/halsubbwgreen");
    
  xdc_register(position_data_encode, position_data_decode, DATA_TYP_POSITION);
  xdc_register(distance_data_encode, distance_data_decode, DATA_TYP_DISTANCE);
}
