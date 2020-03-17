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
    setUAVLocation(uav->getPosition());
  } else if (gps) {
    tick = true; // yeah.. hackish
  } else if (rf) {
    if (!orange_enclave) {
      setDistance(rf->getDistance());
    }
    else {
      updateRemote(s);  // do an RPC call
      return;
    }
  }
		
  if (tick && _cycle != 0 && 0 == ++cnt % _cycle) {
    targetLocation();
    print_track();
    notify();
  }
}

void Target::targetLocation() {
  _track._pos._x = _uav_pos._x + _d._dx;
  _track._pos._y = _uav_pos._y + _d._dy;
  _track._pos._z = _uav_pos._z + _d._dz;
}
