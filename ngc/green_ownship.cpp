#include "ownship.h"
#include "sensors.h"
#include "rpc.h"

#include "xdcomms.h"
#include "gma.h"

// Depending on whether the subject is same or diff color, update may be local or xd
void OwnShip::update(Subject *s) {
  static int cnt = 0;
  GpsSensor *gps = dynamic_cast<GpsSensor *>(s);
  if (gps) {
    updateRemote(s);  // push the position to orange via an RPC

    setPosition(gps->getPosition());
    //setVelocity(gps->getVelocity());
    return;
  }
  if(_cycle != 0 && 0 == ++cnt % _cycle) {
    print_track();
    notify();
  }
}

#ifdef USE_REAL_RPC

void OwnShip::updateRemote(Subject *s) {
  GpsSensor *gps = dynamic_cast<GpsSensor *>(s);
  if (!gps) {
      return;
  }

  Position position = gps->getPosition();
  double x = position._x;
  double y = position._y;
  double z = position._z;
  rpc::client client("127.0.0.1", UAV_PORT);
  auto result = client.call("position", x, y, z).as<std::string>();
  // std::cout << "update UAV position result is: " << result << std::endl;
}

#else // USE_REAL_RPC

void OwnShip::updateRemote(Subject *s) {
  GpsSensor *gps = dynamic_cast<GpsSensor *>(s);
  if (!gps) {
    return;
  }
  Position position  = gps->getPosition();

  gaps_tag  t_tag, r_tag;
  uint32_t  t_mux = 1, t_sec = 1, type = DATA_TYP_POSITION;

  tag_write(&t_tag, t_mux, t_sec, type);
  xdc_asyn_send((uint8_t *) &position, sizeof(double) * 8,  t_tag);
}

#endif
