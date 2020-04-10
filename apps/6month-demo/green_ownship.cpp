#include "ownship.h"
#include "sensors.h"

#include "hal_xdcomms.h"
#include "hal_gma.h"

// Depending on whether the subject is same or diff color, update may be local or xd
void OwnShip::update(Subject *s) {
}

void OwnShipShadow::update(Subject *s) {
  GpsSensor *gps = dynamic_cast<GpsSensor *>(s);
  if (!gps) {
    return;
  }
  Position position  = gps->getPosition();
  position_datatype pos;
  pos.x = position._x;
  pos.y = position._y;
  pos.z = position._z;
  pos.trailer.seq = seq;
  pos.trailer.rqr = rqr;
  pos.trailer.oid = oid;
  pos.trailer.mid = mid;
  pos.trailer.crc = crc;

  #pragma cle begin TAG_1_1_1
  gaps_tag  t_tag;
  #pragma cle end TAG_1_1_1
  uint32_t  t_mux = 1, t_sec = 1, type = DATA_TYP_POSITION;

  tag_write(&t_tag, t_mux, t_sec, type);

  if (send_pos_socket == NULL)
      send_pos_socket = xdc_pub_socket();
  xdc_asyn_send(send_pos_socket, &pos, &t_tag);
}
