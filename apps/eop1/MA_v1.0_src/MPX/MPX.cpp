#include "TOI.h"
#include "MPX.h"
#include "Utils.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <fstream>
#include <time.h>
#include <chrono>
#include <ctime>  


using namespace std;
using namespace std::placeholders;

MPX::MPX(MissionPlan *plan) : planManager(5), toiList(30) {
	json j = Utils::loadDefaultConfig();
	processConfigDefaultContent(j);
	running = false;
	updateMissionPlan(plan);
	amq.listen("updateMissionPlan", std::bind(&MPX::handleNewPlan, this, _1), true);
	amq.listen("recieveISRMDetections", std::bind(&MPX::recieveISRMDetections, this, _1), true);
	amq.listen("updateConfig", std::bind(&MPX::handleUpdateConfig, this, _1), true);
}

MPX::MPX() : planManager(5), toiList(30) {
	json j = Utils::loadDefaultConfig();
	processConfigDefaultContent(j);
	running = false;
	amq.listen("updateMissionPlan", std::bind(&MPX::handleNewPlan, this, _1), true);
	amq.listen("recieveISRMDetections", std::bind(&MPX::recieveISRMDetections, this, _1), true);
	amq.listen("updateConfig", std::bind(&MPX::handleUpdateConfig, this, _1), true);
}

void MPX::setSpeed(double speed) {
	this->speed = speed;
}

void MPX::setLocation(double lat, double lon, double alt) {
	location.y = lat;
	location.x = lon;
	location.z = alt;
}

void MPX::processConfigDefaultContent(json j) {
	string sp = "speed";
	string lat = "lat";
	string lon = "lon";
	string alt = "alt";
	setSpeed(j[sp]);
	setLocation(j[lat], j[lon], j[alt]);
}

void MPX::processConfigContent(json j) {
	string sp = "speed";
	setSpeed(j[sp]);
}

void MPX::handleUpdateConfig(json j) {
	json k = Utils::loadConfig(j);
	processConfigContent(k);
}

MPX::~MPX() {
	planManager.clearAll();
	toiList.clearAll();
}

void MPX::run() {
	std::thread t1(&MPX::checkPlanStatus, this, std::ref(planManager));
	t1.detach();
	std::thread t2(&MPX::printInformation, this);
	t2.detach();
}

void MPX::updateMissionPlan(MissionPlan *plan) {
	planManager.add(plan->getId(), plan);
	changed = true;
}

void MPX::setChanged(const bool &c) {
	changed = c;
}

void MPX::printInformation() {
	while (!missionComplete && running) {
		if (planManager.getCurrent() != nullptr) {
			cout << "Executing.." << endl;
			cout << "Elapsed Time: " << time(&timer) - startTime << "s" << endl;
			cout << "Current Location: " << "[" << location.y << ", " << location.x << "]" << endl;
			cout << "Bearing: " << bearing << endl;
			cout << "Plan ID: " << planManager.getCurrent()->getId() << endl;
			planManager.getCurrent()->printInformation();
			cout << "Remaining Distance: " << distance << " km" << endl;
			cout << "Speed: " << speed << " km/s" << endl;
			cout << "Phase: " << phase << endl;
			cout << "-----------------------------------" << endl;
			Utils::sleep_for(1000);
		}
	}
}

void MPX::handleNewPlan(json j) {
	running = false;
	updateMissionPlan(Utils::parsePlan(j));
	running = true;
	run();
}

void MPX::checkPlanStatus(Store<MissionPlan*> &planManager) {
	auto tb = std::chrono::steady_clock::now();
	while (running) {
		auto dur = std::chrono::steady_clock::now() - tb;
		auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
		if (ms > 1000) {
			if (planManager.getCurrent() != nullptr) {
				if (changed) {
					changed = false;
					schedule = 0;
				}
				tb = std::chrono::steady_clock::now();
				Utils::getNextLatLon(location.y, location.x, planManager.getCurrent()->getHeadSchedule()->getX(),
					planManager.getCurrent()->getHeadSchedule()->getY(), speed);
				json j = json::object();
				j["lat"] = location.y;
				j["lon"] = location.x;
				j["alt"] = planManager.getCurrent()->getHeadSchedule()->getZ();
				j["time"] = time(&timer);
				amq.publish("pnt", j, true);
				distance = Utils::distanceEarth(location.y, location.x,
					planManager.getCurrent()->getHeadSchedule()->getX(),
					planManager.getCurrent()->getHeadSchedule()->getY());
				bearing = Utils::bearing(location.y, location.x,
					planManager.getCurrent()->getHeadSchedule()->getX(),
					planManager.getCurrent()->getHeadSchedule()->getY()
				);
				if (Utils::isNear(distance, speed + 0.1)) {
					if (planManager.getCurrent()->getHeadSchedule()->isEgressPoint()) {
						missionComplete = true;
						if (fixStarted) {
							requestISRMDetections("fix");
						}
						if (findStarted) {
							requestISRMDetections("find");
						}
						break;
					}
					planManager.getCurrent()->popSchedule();
					Utils::getNextLatLon(location.y, location.x, planManager.getCurrent()->getHeadSchedule()->getX(),
						planManager.getCurrent()->getHeadSchedule()->getY(), speed);
					phase = planManager.getCurrent()->getHeadSchedule()->getPhase();
					if (phase == "find") {
						findStarted = true;
					}
					else if (phase != "find" && findStarted) {
						requestISRMDetections("find");
						findStarted = false;
					}
					if (phase == "fix") {
						fixStarted = true;
					}
					else if (phase != "fix" && fixStarted) {
						requestISRMDetections("fix");
						fixStarted = false;
					}
				}
			}

		}

	}
}

void MPX::recieveISRMDetections(json j) {
	cout << j << endl;
	for (int i = 0; i < j.size(); i++) {
		string id = j[i]["TGT_ISRM_ID"];
		double xD = j[i]["lat"];
		double yD = j[i]["lon"];
		double zD = j[i]["alt"];
		double speed = j[i]["speed"];
		double bearing = j[i]["bearing"];
		double conf = j[i]["confidence"];
		string classification = j[i]["classification"];
		if (toiList.contains(id)) {
			toiList.get(id)->setSpeedAndBearing(speed, bearing);
		}
		else {
			TOI *toi = new TOI(id, xD, yD, zD, speed, bearing, conf, classification);
			toiList.add(id, toi);
		}

	}
	printTOIList();
}

void MPX::requestISRMDetections(const string &phase) {
	json js;
	js["phase"] = phase;
	amq.publish("requestISRMDetections", js, true);
}

void MPX::printTOIList() {
	for (const auto& key_value : toiList.getMap()) {
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


