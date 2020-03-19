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
  } else if (gps) {
    tick = true; // yeah.. hackish
  } else if (rf) {
    setDistance(rf->getDistance());
  }
		
  if (tick && _cycle != 0 && 0 == ++cnt % _cycle) {
    targetLocation();
    print_track();
    notify();
  }
}

void TargetShadow::update(Subject *s) {
  OwnShip *uav = dynamic_cast<OwnShip *>(s);
  RfSensor *rf = dynamic_cast<RfSensor *>(s);
  if (uav) {
    Position position  = uav->getPosition();
    position_datatype pos;
    pos.x = position._x;
    pos.y = position._y;
    pos.z = position._z;
    pos.trailer.seq = seq;
    pos.trailer.rqr = rqr;
    pos.trailer.oid = oid;
    pos.trailer.mid = mid;
    pos.trailer.crc = crc;

    gaps_tag  t_tag, r_tag;
    uint32_t  t_mux = 2, t_sec = 2, type = DATA_TYP_POSITION;

    tag_write(&t_tag, t_mux, t_sec, type);
    xdc_asyn_send((uint8_t *) &pos, t_tag);
  }
  else if (rf) {
    Distance distance  = rf->getDistance();
    position_datatype dis;
    dis.x = distance._dx;
    dis.y = distance._dy;
    dis.z = distance._dz;
    dis.trailer.seq = seq;
    dis.trailer.rqr = rqr;
    dis.trailer.oid = oid;
    dis.trailer.mid = mid;
    dis.trailer.crc = crc;

    gaps_tag  t_tag, r_tag;
    uint32_t  t_mux = 2, t_sec = 2, type = DATA_TYP_DISTANCE;

    tag_write(&t_tag, t_mux, t_sec, type);
    xdc_asyn_send((uint8_t *) &dis, t_tag);
  }

  Target::update(s);
}

void Target::targetLocation() {
  _track._pos._x = _uav_pos._x + _d._dx;
  _track._pos._y = _uav_pos._y + _d._dy;
  _track._pos._z = _uav_pos._z + _d._dz;
}
