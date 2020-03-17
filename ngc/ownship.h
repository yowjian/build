#pragma once
#include "pnt_data.h"
#include "observer.h"
#include "sensors.h"
#include "rpc.h"
#include "rpc/client.h"

#include <iostream>

class OwnShip: public Observer, public Subject
{
#pragma cle begin ORANGE_POSITION
  Track _track;
#pragma cle end ORANGE_POSITION
  int _frequency;
  int _cycle;

public:
  OwnShip(int rate = 1) : _frequency(rate) {
    _cycle = static_cast<int> (((1.0 / _frequency) / (sleep_msec / 1000)));
  };
  ~OwnShip() {};

  Position getPosition() { return _track._pos; }
  Track getTracking() { return _track; }

  virtual void update(Subject *s) override;
  
  void notify() override {
    for (auto e : _observers)
      e->update(this);
  }
int count = 0;
  void print_track()
  {
    std::cout << ++count << " ---UAV TRACK ---" << std::endl
	      << " x=" << _track._pos._x << std::endl
	      << " y=" << _track._pos._y << std::endl
	      << " z=" << _track._pos._z << std::endl << std::endl;
  }
  void setPosition(Position const& p) { _track._pos = p; }
protected:
  void setVelocity(Velocity const& v) { _track._v = v; }
  
  void updateRemote(Subject *s) {
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
};
