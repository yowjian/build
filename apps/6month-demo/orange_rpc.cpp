#include "target.h"

#include "hal_xdcomms.h"
#include "hal_gma.h"

void GpsSensorShadow::receive()
{
    #pragma cle begin TAG_1_1_1
    gaps_tag t_tag;
    #pragma cle end TAG_1_1_1
    uint32_t t_mux = 1, t_sec = 1, type = DATA_TYP_POSITION;

    tag_write(&t_tag, t_mux, t_sec, type);
    void *socket = xdc_sub_socket(t_tag);

    Position position;
    position_datatype pos;

    while (1) {
        xdc_blocking_recv(socket, &pos, &t_tag);

        position._x = pos.x;
        position._y = pos.y;
        position._z = pos.z;

        setPosition(position);
        notify();
    }
    zmq_close(socket);
}

void *hal_init()
{
    void *ctx = xdc_ctx();
    xdc_set_out((char *)"ipc:///tmp/halpubbworange");
    xdc_set_in((char *)"ipc:///tmp/halsubbworange");

    xdc_register(position_data_encode, position_data_decode, DATA_TYP_POSITION);
    xdc_register(distance_data_encode, distance_data_decode, DATA_TYP_DISTANCE);

    return ctx;
}
