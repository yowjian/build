#include <iostream>

#include "ownship.h"

#include "hal_xdcomms.h"
#include "hal_gma.h"

void OwnShipShadow::receive()
{
    while (1) {
        Position position(0, 0, 0);
	position_datatype pos;

        gaps_tag  t_tag, r_tag;
        uint32_t  t_mux = 2, t_sec = 2, type = DATA_TYP_POSITION;

        tag_write(&t_tag, t_mux, t_sec, type);

        size_t len = sizeof(double) * 8;
        xdc_blocking_recv(&pos, &t_tag);

	position._x = pos.x;
	position._y = pos.y;
	position._z = pos.z;

        setPosition(position);
        notify();
    }
}

void RfSensorShadow::receive()
{
    while (1) {
        Distance distance(0, 0, 0);
	distance_datatype dis;
	
        gaps_tag  t_tag, r_tag;
        uint32_t  t_mux = 2, t_sec = 2, type = DATA_TYP_DISTANCE;

        tag_write(&t_tag, t_mux, t_sec, type);

        size_t len = sizeof(double) * 8;
        xdc_blocking_recv(&dis, &t_tag);

	distance._dx = dis.x;
	distance._dy = dis.y;
	distance._dz = dis.z;	

        setDistance(distance);
        notify();
    }
}

void hal_init()
{
  xdc_set_out((char *)"ipc:///tmp/halpubbwgreen");
  xdc_set_in((char *)"ipc:///tmp/halsubbwgreen");
    
  xdc_register(position_data_encode, position_data_decode, DATA_TYP_POSITION);
  xdc_register(distance_data_encode, distance_data_decode, DATA_TYP_DISTANCE);
}
