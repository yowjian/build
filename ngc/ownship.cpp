#include "ownship.h"
#include "sensors.h"

// Depending on whether the subject is same or diff color, update may be local or xd
void OwnShip::update(Subject *s) {
  if (!_orange) {
      updateRemote(s);
      return;
  }
  static int cnt = 0;
  GpsSensor *gps = dynamic_cast<GpsSensor *>(s);
  if (gps) {
    setPosition(gps->getPosition());
    //setVelocity(gps->getVelocity());
  }
  if(_cycle != 0 && 0 == ++cnt % _cycle) {
    print_track();
    notify();
  }
}

