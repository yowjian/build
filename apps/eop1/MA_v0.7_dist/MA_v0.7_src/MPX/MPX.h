#pragma once
#ifndef MPX_H
#define MPX_H
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
# include <Windows.h>
#else
# include <unistd.h>
#endif
#include <chrono>
#include <missions/MissionPlan.h>
#include <nlohmann/json.hpp>
#include "Utils.h"
#include <thread>
#include <iostream>
#include <time.h>
#include <chrono>
#include <ctime>  
#include <amqm/AMQManager.h>
#include <unordered_set>
#include <functional>
#include <Store.h>
#include "TOI.h"


using namespace std;
using namespace uas;
using namespace amqm;
using namespace std::placeholders;

using json = nlohmann::json;
class MPX {
public:
	MPX(MissionPlan *plan) {
		updateMissionPlan(plan);
		init();
	}
	MPX() {
		amq.listen("updateMissionPlan", std::bind(&MPX::handleNewPlan, this, _1), true);
		amq.listen("recieveISRMDetections", std::bind(&MPX::recieveISRMDetections, this, _1), true);
		classifications.insert("person");
		classifications.insert("tank");
		init();
	}
	
	void updateMissionPlan(MissionPlan *plan) {
		planManager->add(plan->getId(), plan);
		changed = true;
	}

	void setChanged(const bool &c) {
		changed = c;
	}

	void printInformation() {
		cout << "Executing.." << endl;
		cout << "Elapsed Time: " << time(&timer) - startTime << "s" << endl;
		cout << "Current Location: " << "[" << lat << ", " << lon << "]" << endl;
		cout << "Bearing: " << bearing << endl;
		planManager->getCurrent()->printInformation(schedule);
		cout << "Remaining Distance: " << distance << " km" << endl;
		cout << "Speed: " << speed << " km/s" << endl;
		cout << "-----------------------------------" << endl;
#ifdef _WIN32	  
		Sleep(sleep_msec); // 100 Hz
#else
		usleep(sleep_msec * 1000);

#endif
	}
	void checkPlanStatus(Store<MissionPlan*> *planManager) {
		auto tb = std::chrono::steady_clock::now();
		while (true) {
				auto dur = std::chrono::steady_clock::now() - tb;
				auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
				if (ms > 1000) {
					if (planManager->getCurrent() != nullptr) {
						if (changed) {
							changed = false;
							schedule = 0;
						}
						tb = std::chrono::steady_clock::now();
						Utils::getNextLatLon(lat, lon, planManager->getCurrent()->getSchedule(schedule)->getX(),
							planManager->getCurrent()->getSchedule(schedule)->getY(), speed);
						json j = json::object();
						j["lat"] = lat;
						j["lon"] = lon;
						j["alt"] = planManager->getCurrent()->getSchedule(schedule)->getZ();
						j["time"] = time(&timer);
						amq.publish("pnt", j, true);
						distance = Utils::distanceEarth(lat, lon,
							planManager->getCurrent()->getSchedule(schedule)->getX(),
							planManager->getCurrent()->getSchedule(schedule)->getY());
						bearing = Utils::bearing(lat, lon,
							planManager->getCurrent()->getSchedule(schedule)->getX(),
							planManager->getCurrent()->getSchedule(schedule)->getY()
						);
						if (Utils::isNear(distance, 0.5)) {
							schedule++;
							if (schedule >= planManager->getCurrent()->getScheduleSize()) {
								requestISRMDetections("fix");
								missionComplete = true;
								break;
							}
							else if(planManager->getCurrent()->getSchedule(schedule)->getPhase() == "fix") {
								requestISRMDetections("find");
							}
							Utils::getNextLatLon(lat, lon, planManager->getCurrent()->getSchedule(schedule)->getX(),
								planManager->getCurrent()->getSchedule(schedule)->getY(), speed);
						}
					}

				}

		}
	}
	void setWayPoint(int wp) {
		schedule = wp;
	}

private:
	AMQManager amq;
	void handleNewPlan(json j) {
		updateMissionPlan(Utils::parsePlan(j));
	}
	void requestISRMDetections(const string &phase) {
		json js;
		js["phase"] = phase;
		amq.publish("requestISRMDetections", js, true);
	}

	void recieveISRMDetections(json j) {
		for (int i = 0; i < j.size(); i++) {
			int idn = j[i]["TGT_ISRM_ID"];
			string id = to_string(idn);
			double xD = j[i]["x"];
			double yD = j[i]["y"];
			double zD = 0;
			double speed = j[i]["speed"];
			double bearing = j[i]["bearing"];
			double conf = j[i]["confidence"];
			string classification = j[i]["classification"];
			if (conf >= this->confidence) {
				if (toiList->contains(id)) {
					toiList->get(id)->setSpeedAndBearing(speed, bearing);
				}
				else {
					TOI *toi = new TOI(id, xD, yD, zD, speed, bearing, conf, classification);
					toiList->add(id, toi);
				}

			}
		}
		printTOIList();
	}

	void printTOIList() {
		for (const auto& key_value : toiList->getMap()) {
			cout << "ID: " << key_value.second->getId() << endl;
			cout << "Speed: " << key_value.second->getSpeed() << endl;
			cout << "Bearing: " << key_value.second->getBearing() << endl;
			cout << "X: " << key_value.second->getX() << endl;
			cout << "Y: " << key_value.second->getY() << endl;
			cout << "Z: " << key_value.second->getZ() << endl;
			cout << "Classification: " << key_value.second->getClassification() << endl;
			cout << "Confidence : " << key_value.second->getConfidence() << endl;
		}
		cout << "----------------------" << endl;
	}

	void init() {
		std::thread t1(&MPX::checkPlanStatus, this, planManager);
		t1.detach();
		//std::thread t2(&MPX::printInformation, this);
		//t2.detach();
	}
	int sleep_msec = 1000;
	time_t timer;
	long startTime = time(&timer);
	Store<MissionPlan*> *planManager = new Store<MissionPlan*>(5);
	Store<TOI*> *toiList = new Store<TOI*>(50);
	double lat = 0;
	double lon = 0;
	int schedule = 0;
	double speed = 0.9;
	const double confidence = 0.4;
	unordered_set<string> classifications;
	double distance = 0;
	double bearing = 0;
	bool changed = false;
	bool missionComplete = false;
};
#endif
