#include <iostream>
#include "rpc/server.h"
#include "rpc.h"

#include "ownship.h"
#include "target.h"

#include "hal_xdcomms.h"
#include "hal_gma.h"

OwnShip* uav = NULL;
Target* tgt = NULL;

void *rpc_server(void *args)
{
    while (1) {
        Position position  = uav->getPosition();

        gaps_tag  t_tag, r_tag;
        uint32_t  t_mux = 1, t_sec = 1, type = DATA_TYP_POSITION;

        tag_write(&t_tag, t_mux, t_sec, type);

        size_t len = sizeof(double) * 3;
        xdc_blocking_recv((uint8_t *) &position, &t_tag);

        Velocity v(0, 0, 0);  // don't care
        GpsSensor* gps = new GpsSensor(position, v);
        uav->update(gps);
    }

    return 0;
}

void rpc_init(OwnShip* u, Target* t)
{
   uav = u;
   tgt = t;

   pthread_t rpcThread;

   xdc_set_out((char *)"ipc:///tmp/halpubbworange");
   xdc_set_in((char *)"ipc:///tmp/halsubbworange");

   xdc_register(position_data_encode, position_data_decode, DATA_TYP_POSITION);
   xdc_register(distance_data_encode, distance_data_decode, DATA_TYP_DISTANCE);

   int rpcThreadID = pthread_create(&rpcThread, NULL, &rpc_server, NULL);
   if (rpcThreadID != 0) {
        throw std::runtime_error("RPC thrad create failed.");
   }
}
