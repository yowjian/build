#include "target.h"
#include "ownship.h"
#include "sensors.h"
#include "rpc.h"

#include "xdcomms.h"
#include "gma.h"

void Target::update(Subject *s) {
  static int cnt = 0;
  bool tick = false;
  
  OwnShip *uav = dynamic_cast<OwnShip *>(s);
  GpsSensor *gps = dynamic_cast<GpsSensor *>(s);
  RfSensor *rf = dynamic_cast<RfSensor *>(s);
  if (uav) {
    setUAVLocation(uav->getPosition());
    // push UAV position to green via RPC
    updateRemote(s);
  } else if (gps) {
    tick = true; // yeah.. hackish
  } else if (rf) {
    setDistance(rf->getDistance());
    // push the distance to green via RPC
    updateRemote(s);
  }
		
  if (tick && _cycle != 0 && 0 == ++cnt % _cycle) {
    targetLocation();
    print_track();
    notify();
  }
}

#ifdef USE_REAL_RPC

void Target::updateRemote(Subject *s) {
  OwnShip *uav = dynamic_cast<OwnShip *>(s);
  RfSensor *rf = dynamic_cast<RfSensor *>(s);
  if (uav) {
    Position position  = uav->getPosition();
    double x = position._x;
    double y = position._y;
    double z = position._z;
    rpc::client client("127.0.0.1", TARGET_PORT);
    auto result = client.call("uav", x, y, z).as<std::string>();
  }
  else if (rf) {
    Distance distance  = rf->getDistance();
    double x = distance._dx;
    double y = distance._dy;
    double z = distance._dz;
    rpc::client client("127.0.0.1", TARGET_PORT);
    auto result = client.call("distance", x, y, z).as<std::string>();
  }
}
#else // USE_REAL_RPC

void Target::updateRemote(Subject *s) {
  OwnShip *uav = dynamic_cast<OwnShip *>(s);
  RfSensor *rf = dynamic_cast<RfSensor *>(s);
  if (uav) {
    Position position  = uav->getPosition();

    gaps_tag  t_tag, r_tag;
    uint32_t  t_mux = 2, t_sec = 2, type = DATA_TYP_POSITION;

    tag_write(&t_tag, t_mux, t_sec, type);
    xdc_asyn_send((uint8_t *) &position, sizeof(double) * 8,  t_tag);
  }
  else if (rf) {
    Distance distance  = rf->getDistance();

    gaps_tag  t_tag, r_tag;
    uint32_t  t_mux = 2, t_sec = 2, type = DATA_TYP_DISTANCE;

    tag_write(&t_tag, t_mux, t_sec, type);
    xdc_asyn_send((uint8_t *) &distance, sizeof(double) * 8,  t_tag);
  }
}

#endif

void Target::targetLocation() {
  _track._pos._x = _uav_pos._x + _d._dx;
  _track._pos._y = _uav_pos._y + _d._dy;
  _track._pos._z = _uav_pos._z + _d._dz;
}
