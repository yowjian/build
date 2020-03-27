#include <iostream>

#include "rpc.h"

#include "ownship.h"
#include "target.h"

#include "hal_xdcomms.h"
#include "hal_gma.h"

OwnShip* uav = NULL;
Target* tgt = NULL;

void *uav_server(void *args)
{
    while (1) {
        Position position(0, 0, 0);

        gaps_tag  t_tag, r_tag;
        uint32_t  t_mux = 2, t_sec = 2, type = DATA_TYP_POSITION;

        tag_write(&t_tag, t_mux, t_sec, type);

        size_t len = sizeof(double) * 8;
        xdc_blocking_recv((uint8_t *) &position, &t_tag);
        uav->setPosition(position);
        tgt->update(uav);
    }

    return 0;
}

void *rfs_server(void *args)
{
    while (1) {
        Distance distance(0, 0, 0);

        gaps_tag  t_tag, r_tag;
        uint32_t  t_mux = 2, t_sec = 2, type = DATA_TYP_DISTANCE;

        tag_write(&t_tag, t_mux, t_sec, type);

        size_t len = sizeof(double) * 8;
        xdc_blocking_recv((uint8_t *) &distance, &t_tag);
        Velocity vtgt(0, 0, 0);  // don't care
        RfSensor* rfs = new RfSensor(distance, vtgt);
        tgt->update(rfs);
    }
    return 0;
}

void rpc_init(OwnShip* u, Target* t)
{
  xdc_set_out((char *)"ipc:///tmp/halpubbwgreen");
  xdc_set_in((char *)"ipc:///tmp/halsubbwgreen");
    
  xdc_register(position_data_encode, position_data_decode, DATA_TYP_POSITION);
  xdc_register(distance_data_encode, distance_data_decode, DATA_TYP_DISTANCE);

  uav = u;
  tgt = t;

  pthread_t uavThread;
  int uavThreadID = pthread_create(&uavThread, NULL, &uav_server, NULL);
  if (uavThreadID != 0) {
      throw std::runtime_error("UAV thrad create failed.");
  }

  pthread_t rfsThread;
  int rgsThreadID = pthread_create(&rfsThread, NULL, &rfs_server, NULL);
  if (rgsThreadID != 0) {
      throw std::runtime_error("RFS thrad create failed.");
  }
}
