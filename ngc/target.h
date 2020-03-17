#pragma once
#include "pnt_data.h"
#include "observer.h"
#include "sensors.h"
#include <iostream> 
#include "rpc.h"
#include "rpc/client.h"

class Target : public Observer, public Subject
{
public:
  Distance  _d;
  Position _uav_pos;
  Track _track;
  int _frequency;
  int _cycle;

public:
  Target(int rate = 1) : _frequency(rate) {
    _cycle = static_cast<int> (((1.0 / _frequency) / (sleep_msec / 1000)));
  };
  ~Target() {};

  Track getTracking() { return _track; }
  
  void update(Subject* s) override;
  void notify() override {
    for (auto e : _observers)
      e->update(this);
  }
  
  void print_track() {
    std::cout << "\t\t--- Target TRACK ---" << std::endl
	      << "\t\t x=" << _track._pos._x << std::endl
	      << "\t\t y=" << _track._pos._y << std::endl
	      << "\t\t z=" << _track._pos._z << std::endl << std::endl;
  }

protected:
  void setDistance(Distance const& d)    { _d = d; }
  void setUAVLocation(Position const& p) { _uav_pos = p; }


  void updateRemote(Subject *s) {
    RfSensor *rf = dynamic_cast<RfSensor *>(s);
    if (!rf) {
        return;
    }

    Distance distance  = rf->getDistance();
    double x = distance._dx;
    double y = distance._dy;
    double z = distance._dz;
    rpc::client client("127.0.0.1", TARGET_PORT);
    auto result = client.call("distance", x, y, z).as<std::string>();
    // std::cout << "update TARGET result is: " << result << std::endl;
  }

private:
  void targetLocation();
};

