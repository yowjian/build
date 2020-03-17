#include "target.h"
#include "ownship.h"
#include "sensors.h"
#include "rpc.h"

void Target::update(Subject *s) {
  static int cnt = 0;
  bool tick = false;
  
  OwnShip *uav = dynamic_cast<OwnShip *>(s);
  GpsSensor *gps = dynamic_cast<GpsSensor *>(s);
  RfSensor *rf = dynamic_cast<RfSensor *>(s);
  if (uav) {
    if (!orange_enclave) {
      setUAVLocation(uav->getPosition());
    }
    else {
      // push UAV position to green via RPC
      updateRemote(s);
      return;
    }
  } else if (gps) {
    tick = true; // yeah.. hackish
  } else if (rf) {
    if (!orange_enclave) {
      // should not happen as rf is in the orange enclave
      setDistance(rf->getDistance());
    }
    else {
      // push the distance to green via RPC
      updateRemote(s);
      return;
    }
  }
		
  if (tick && _cycle != 0 && 0 == ++cnt % _cycle) {
    targetLocation();
    print_track();
    notify();
  }
}

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

void Target::targetLocation() {
  _track._pos._x = _uav_pos._x + _d._dx;
  _track._pos._y = _uav_pos._y + _d._dy;
  _track._pos._z = _uav_pos._z + _d._dz;
}
