#pragma once
#include "pnt_data.h"
#include "observer.h"
#include "sensors.h"
#include "hal_xdcomms.h"

#include <iostream>

class OwnShip: public Observer, public Subject
{
  Track _track;
  int _frequency;
  int _cycle;
  RfSensor *_rfs;

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

  void print_track()
  {
    std::cout << "---UAV TRACK ---" << std::endl
	      << " x=" << _track._pos._x << std::endl
	      << " y=" << _track._pos._y << std::endl
	      << " z=" << _track._pos._z << std::endl << std::endl;
  }
  // CHANGE: from protected
  void setPosition(Position const& p) { _track._pos = p; }
    
  void registerSensor(RfSensor *rfs) { _rfs = rfs; }
  
protected:
  void setVelocity(Velocity const& v) { _track._v = v; }
};

class OwnShipShadow: public OwnShip, public Trailer
{
private:
    std::thread thread_;
    void receive();
    void *send_pos_socket = NULL;

public:
  OwnShipShadow(int rate = 1) {
      thread_ = std::thread(&OwnShipShadow::receive, this);
  }
  ~OwnShipShadow() {
      if (send_pos_socket != NULL)
          zmq_close(send_pos_socket);
      thread_.join();
  }

  void notify() override {
      OwnShip::notify();
  }

  virtual void update(Subject *s) override;

};
