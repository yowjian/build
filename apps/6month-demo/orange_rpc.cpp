#include "target.h"

#include "hal_xdcomms.h"
#include "hal_gma.h"

void GpsSensorShadow::receive()
{
    while (1) {
        Position position;
	position_datatype pos;
	
        gaps_tag  t_tag, r_tag;
        uint32_t  t_mux = 1, t_sec = 1, type = DATA_TYP_POSITION;

        tag_write(&t_tag, t_mux, t_sec, type);

        size_t len = sizeof(double) * 3;
        xdc_blocking_recv(&pos, &t_tag);
	position._x = pos.x;
	position._y = pos.y;
	position._z = pos.z;	

        setPosition(position);
        notify();
    }
}

void hal_init()
{
   xdc_set_out((char *)"ipc:///tmp/halpubbworange");
   xdc_set_in((char *)"ipc:///tmp/halsubbworange");

   xdc_register(position_data_encode, position_data_decode, DATA_TYP_POSITION);
   xdc_register(distance_data_encode, distance_data_decode, DATA_TYP_DISTANCE);
}
