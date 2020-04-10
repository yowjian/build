// pnt_example.cpp : Defines the entry point for the console application.
//

#include <iostream>
#ifdef _WIN32
# include <Windows.h>
#else
# include <unistd.h>
#endif
#include "pnt_data.h"
#include "sensors.h"
#include "ownship.h"
#include "target.h"

#pragma cle def GREEN {"level":"green",\
  "cdf": [\
    {"remotelevel":"==orange", \
     "direction": "egress", \
     "guardhint": { "oneway": "true"}}\
  ] }

#pragma cle def ORANGE {"level":"orange",\
  "cdf": [\
    {"remotelevel":"==green", \
     "direction": "egress", \
     "guardhint": { "oneway": "true"}}\
  ] }

#pragma cle def TAG_1_1_1 {}
#pragma cle def TAG_2_2_1 {}
#pragma cle def TAG_2_2_2 {}

int main(int argc, char **argv)
{
  Position p(.0, .0, .0); // initial position
  Distance d(1062, 7800, 9000); // initial target distance

  Velocity v(50, 25, 12);
  Velocity vtgt(35, 625, 18);
  #pragma cle begin GREEN
  GpsSensor* gps = new GpsSensor(p, v);
  #pragma cle end GREEN
  #pragma cle begin ORANGE
  RfSensor* rfs = new RfSensor(d, vtgt);
    
  OwnShip* uav = new OwnShip(100); // updates at 100 Hz frequency
  #pragma cle end ORANGE
  #pragma cle begin GREEN
  Target* tgt = new Target (10); // updates at 10 Hz frequency
  #pragma cle end GREEN

  // setup the dataflow relationships
  gps->attach(uav);
  gps->attach(tgt);
  uav->attach(tgt);
  rfs->attach(tgt);

  while (true)
    {
      // here we simulate sensor data streams
      gps->read();
      rfs->read();
      
#ifdef _WIN32	  
      Sleep(sleep_msec); // 100 Hz
#else
      usleep(sleep_msec * 1000);
#endif
    }
  return 0;
}

