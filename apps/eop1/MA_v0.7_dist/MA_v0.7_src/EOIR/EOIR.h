#pragma once
#ifndef EOIR_H
#define EOIR_H
#define WIN32_LEAN_AND_MEAN
#ifdef _WIN32
# include <Windows.h>
#else
# include <unistd.h>
#endif
#include <chrono>
#include "Store.h"
#include <missions/MissionPlan.h>
#include "Utils.h"
#include <thread>
#include <iostream>
#include <time.h>
#include <fstream>
#include <missions/CommonUAS.h>
#include <amqm/AMQManager.h>

using namespace std;
using namespace amqm;
using namespace std::placeholders;

struct Detection {
     Detection() {

     }
     uas::Area detectionArea;
     void addArea(double top_left_x, double top_left_y, double bottom_right_x, double bottom_right_y) {
          detectionArea.upper_left = uas::Point(top_left_x, top_left_y);
          detectionArea.bottom_right = uas::Point(bottom_right_x, bottom_right_y);
     }

};
class EOIR {
public:
     EOIR() {
		  amq.listen("groundMovers", std::bind(&EOIR::printInformation, this, _1), false);
		  amq.listen("updateMissionPlan", std::bind(&EOIR::updateMissionPlan, this, _1), true);
          Detection *det = new Detection();
          det->addArea(10, 10, 20, 20);
          detects->add("car1", det);
          std::thread t1(&EOIR::checkDetectionStatus, this, detects);
          t1.detach();
     }
private:
	AMQManager amq;
	void updateMissionPlan(json j) {
		MissionPlan *plan = Utils::parsePlan(j);
		planManager->add(plan->getId(), plan);
	}
	Store<MissionPlan*> *planManager = new Store<MissionPlan*>(5);
	 void printInformation(json j) {
		 cout << j << endl;
	 }
     void printDetections() {
          for (const auto& key_value : detects->getMap()) {
               cout << "id: " << key_value.first << endl;
               cout << "Image Coords" << "(" << key_value.second->detectionArea.upper_left.x << ", " <<
                    key_value.second->detectionArea.upper_left.y << ")" << ", (" << key_value.second->detectionArea.bottom_right.x << ", "
                    << key_value.second->detectionArea.bottom_right.y << ")" << endl;
               cout << "***********" << endl;
          }
     }
     void checkDetectionStatus(Store<Detection*> *detects) {
          while (true) {
               printDetections();
#ifdef _WIN32	  
               Sleep(sleep_msec); // 100 Hz
#else
               usleep(sleep_msec * 1000);
#endif
          }
     }
     uas::Location currLoc;
     int sleep_msec = 1000;
     Store<Detection*> *detects = new Store<Detection*>(30);
};
#endif