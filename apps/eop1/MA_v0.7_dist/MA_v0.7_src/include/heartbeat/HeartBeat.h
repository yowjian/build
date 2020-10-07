#pragma once
#ifndef HEARTBEAT_H
#define HEARTBEAT_H
#define WIN32_LEAN_AND_MEAN
#ifdef _WIN32
# include <Windows.h>
#else
# include <unistd.h>
#endif
#include <amqm/AMQManager.h>

#include "Utils.h"
using namespace amqm;



class HeartBeat
{
public:
     HeartBeat(std::string subSystem_Name)
     {
          MPU_rdy, MPX_rdy, EOIR_rdy, RDR_rdy, ISRM_rdy, all_subs_rdy = false;
          component_Name = subSystem_Name;
     }


     bool startup_HeartBeats(void)
     {
          // Set MPU to ready since it won't call traditional startup command
          MPU_rdy = true;
          //listen until all subsystems have reported in/rdy
          std::cout << "Waiting for subsystems to come online" << std::endl;
          
  
          amq.listen("component_heartbeats", std::bind(&HeartBeat::updateHeartBeat, this, placeholders::_1), true);
          while(all_subs_rdy == false)
          {
// This is WIN32 API
//               Sleep(1000);
              sleep(1);
          }
          

          //publish all systems ready
          json j = json::object();
          j["ss"] = "All";
          j["st"] = "ready";
          amq.publish("component_heartbeats", j, true);
          std::cout << "All subsystems online" << std::endl;
          //clean-up listener thread
          amq.stopListening("component_heartbeats");

          return true;
     }

     

     void startup_Listener(void)
     {
          // Broadcast sub system is ready and listen for the all-rdy message from MPU
          std::cout << component_Name << ": Ready" << "\n";
          while (!all_subs_rdy)
          {
               broadcast_Startup();
               amq.listen("component_heartbeats", std::bind(&HeartBeat::updateHeartBeat, this, placeholders::_1), true);
          }
          //clean-up listener thread
          amq.stopListening("component_heartbeats");
     }

private:
     bool MPU_rdy, MPX_rdy, EOIR_rdy, RDR_rdy, ISRM_rdy, all_subs_rdy;
     std::string component_Name;
     AMQManager amq = AMQManager();

     void broadcast_Startup(void)
     {
          json j = json::object();
          j["ss"] = component_Name;
          j["st"] = "ready";
          amq.publish("component_heartbeats", j, true);
          
     }

     void updateHeartBeat(json j) {
          string ss = "ss";
          //string st = "status";
          if (j[ss] == "EOIR")
          {
               EOIR_rdy = true;
          }
          else if (j[ss] == "MPU")
          {
               MPU_rdy = true;
          }
          else if (j[ss] == "MPX")
          {
               MPX_rdy = true;
          }
          else if (j[ss] == "RDR")
          {
               RDR_rdy = true;
          }
          else if (j[ss] == "ISRM")
          {
               ISRM_rdy = true;
          }
          else if (j[ss] == "EOIR")
          {
               EOIR_rdy = true;
          }
          else if(j[ss] == "All")
          {
               all_subs_rdy = true;
          }

          // Check if all systems are set to ready
          if(EOIR_rdy == true && ISRM_rdy == true && MPX_rdy == true && MPU_rdy == true && EOIR_rdy == true)
          {
               all_subs_rdy = true;
          }

         
     } // end updateHeartBeat()

     void print_System_HeartBeat_Status(void)
     {
          std::cout << "\n";
          std::cout << "MPU: " << (MPU_rdy ? "Ready" : "Not Ready") << "\n";
          std::cout << "MPX: " << (MPX_rdy ? "Ready" : "Not Ready") << "\n";
          std::cout << "EOIR: " << (EOIR_rdy ? "Ready" : "Not Ready") << "\n";
          std::cout << "ISRM: " << (ISRM_rdy ? "Ready" : "Not Ready") << "\n";
          std::cout << "EOIR: " << (EOIR_rdy ? "Ready" : "Not Ready") << "\n";
          std::cout << "RDR: " << (RDR_rdy ? "Ready" : "Not Ready") << "\n";
     }

};


#endif 
