#include "ownship.h"
#include "sensors.h"
#include "rpc.h"

// Depending on whether the subject is same or diff color, update may be local or xd
void OwnShip::update(Subject *s) {
  static int cnt = 0;
  GpsSensor *gps = dynamic_cast<GpsSensor *>(s);
  if (gps) {
    if (!orange_enclave) { // if not the orange enclave,
//       updateRemote(s);  // push the position to orange via an RPC
       return;
    }
    setPosition(gps->getPosition());
    //setVelocity(gps->getVelocity());
  }
  if(_cycle != 0 && 0 == ++cnt % _cycle) {
    print_track();
    notify();
  }
}

//void OwnShip::updateRemote(Subject *s) {
//  GpsSensor *gps = dynamic_cast<GpsSensor *>(s);
//  if (!gps) {
//      return;
//  }
//
//  Position position = gps->getPosition();
//  double x = position._x;
//  double y = position._y;
//  double z = position._z;
//  rpc::client client("127.0.0.1", UAV_PORT);
//  auto result = client.call("position", x, y, z).as<std::string>();
//  // std::cout << "update UAV position result is: " << result << std::endl;
//}

