// pnt_example.cpp : Defines the entry point for the console application.
//

#include <iostream>
#ifdef _WIN32
# include <Windows.h>
#else
# include <unistd.h>
# include <string.h>
#endif
#include "pnt_data.h"
#include "sensors.h"
#include "ownship.h"
#include "target.h"

#include "rpc.h"

int main(int argc, char **argv)
{
   bool orange = false;
   if (argc > 1) {
      if (!strcmp(argv[1], "orange")) {
         orange = true;

         std::cout << "orange " << orange << std::endl;
      }
   }
   
  rpc_init(orange);
   
  // Assume the color for p, d, v, vtgt is inferred from below coloring in constructors
  // Touched on green side gpssensor constructor
  Position p(.0, .0, .0); // initial position
  // Touched on orange side by RFSensor constructor
  Distance d(1062, 7800, 9000); // initial target distance
  // Touched by green side gpssensor constructor
  Velocity v(50, 25, 12);
  // touched by orange side RFSensor constructor
  Velocity vtgt(35, 625, 18);
  #pragma cle begin GREEN
  GpsSensor* gps = new GpsSensor(p, v);
  #pragma cle end GREEN
  #pragma cle begin ORANGE
  RfSensor* rfs = new RfSensor(d, vtgt);
    
  OwnShip* uav = new OwnShip(100, orange); // updates at 100 Hz frequency
  #pragma cle end ORANGE
  #pragma cle begin GREEN
  Target* tgt = new Target (10); // updates at 10 Hz frequency
  #pragma cle end GREEN

  // setup the dataflow relationships
  gps->attach(uav); // cross domain attach gps is green uav is orange
  gps->attach(tgt);
  uav->attach(tgt); // cross domain 
  rfs->attach(tgt); // cross domain 
  // _observers may be tained; contains a mix of local and remote observers; kind of split TBD

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

