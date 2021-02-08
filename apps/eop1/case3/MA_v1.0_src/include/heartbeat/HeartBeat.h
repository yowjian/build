#pragma once
#ifndef HEARTBEAT_H
#define HEARTBEAT_H
#include <amqm/AMQManager.h>

#include "Utils.h"
using namespace amqm;


/**
* @brief – Class responsible for making sure all subsystems are ready before starting the mission
*
* @author – Original Author - Christopher Seay
* @author – Last Edited By - Mases Krikorian
* @date – 8/27/2020
*
* @details – Emitts a json message containing {"ss": "STRING_SUBSYSTEMNAME", "st": "ready"} through ActiveMQ's "component_heartbeats" 
* topic which is sent to all subsystems. All subsystems also listen to this channel and checkmark internally all the subsystems
* that send ready signal until all subsystems show ready. When that happens, MPU signals the start of MA by sending {"ss": "All", "st": "ready"}
* indicating all systems are up and sends a copy of the mission plan to all the subsystems.
*/

class HeartBeat
{
public:
     /**
      * @brief Construct a new Heart Beat object while not re-initalizing the ActiveMQ Manager since that is done by the subsystem
      *
      * 
      * @param SubSystem Name one of the following: EOIR, RDR, MPU, MPX, ISRM
      */
     HeartBeat(std::string subSystem_Name) : amq(false)
     {
       MPU_rdy = false;
       MPX_rdy = false;
       EOIR_rdy = false;
       RDR_rdy = false;
       ISRM_rdy = false;
       ISRMshadow_rdy = false;
       all_subs_rdy = false;
       component_Name = subSystem_Name;
     }

     /**
      * @brief start a loop to listen to status of all subsystems every 500 ms from MPU only. Stop loop when all systems are up.
      * @param VOID
      */
     void startup_HeartBeats(void)
     {
          // Set MPU to ready since it won't call traditional startup command
          MPU_rdy = true;
          //listen until all subsystems have reported in/rdy
          std::cout << "Waiting for subsystems to come online" << std::endl;
          
  
          amq.listen("component_heartbeats", std::bind(&HeartBeat::updateHeartBeat, this, placeholders::_1), true);
          while(all_subs_rdy == false)
          {
			  Utils::sleep_for(500);
          }
          

          //publish all systems ready
          json j = json::object();
          j["ss"] = "All";
          j["st"] = "ready";
          amq.publish("component_heartbeats", j, true);
          std::cout << "All subsystems online" << std::endl;
          //clean-up listener thread
          amq.stopListening("component_heartbeats");
     }

     
     /**
      * @brief start a loop to listen to status of all subsystems every 1000ms as well as broadcast current status. Stops loop when all systems are up.
      * @param VOID
      * @return VOID
      */
     void startup_Listener(void)
     {
          // Broadcast sub system is ready and listen for the all-rdy message from MPU
          std::cout << component_Name << ": Ready" << "\n";
		  amq.listen("component_heartbeats", std::bind(&HeartBeat::updateHeartBeat, this, placeholders::_1), true);
          while (!all_subs_rdy)
          {
               broadcast_Startup();
			   Utils::sleep_for(1000);
          }
          //clean-up listener thread
          amq.stopListening("component_heartbeats");
     }

private:
     ///@{
     /**
      * @brief boolean variable for each subsystem status
      * 
      */
     bool MPU_rdy, MPX_rdy, EOIR_rdy, RDR_rdy, ISRM_rdy, ISRMshadow_rdy, all_subs_rdy;
     ///@} 
     /**
      * @brief name of subsystem using heartbeat
      * 
      */
     std::string component_Name;
     /**
      * @brief ActiveMQ Manager instance to listen and publish messages
      * 
      */
     AMQManager amq;
     /**
      * @brief broadcast the name of the system and the ready status to all other heartbeart listeners
      * @param VOID
      * @return VOID
      */
     void broadcast_Startup(void)
     {
          json j = json::object();
          j["ss"] = component_Name;
          j["st"] = "ready";
          amq.publish("component_heartbeats", j, true);
          
     }
     /**
      * @brief handle the broadcast of other systems and set their status to true based on string value
      * 
      * @param j contains key "ss": subsystem name
      * @return VOID
      */
     void updateHeartBeat(json j) {
          string ss = "ss";
          //string st = "status";
          if (j[ss] == "MPU")
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
          else if (j[ss] == "ISRMshadow")
          {
               ISRMshadow_rdy = true;
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
          if((EOIR_rdy == true) && (ISRM_rdy == true) && (ISRMshadow_rdy == true) && (MPX_rdy == true) && (MPU_rdy == true) && (RDR_rdy == true))
          {
               all_subs_rdy = true;
          }

         
     } // end updateHeartBeat()
     /**
      * @brief DEBUG method to print the status of all the subsystems in each process.
      * @param VOID
      * @return VOID
      */
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
