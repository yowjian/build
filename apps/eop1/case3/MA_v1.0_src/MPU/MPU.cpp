#include "MPU.h"
#include <fstream>
#include <iostream>


using namespace std;
using namespace std::placeholders;



MPU::MPU() : planManager(5) {
	amq.listen("updateNewTasking", std::bind(&MPU::updateNewTasking, this, _1), true);
	amq.listen("updateConfig", std::bind(&MPU::handleUpdateConfig, this, _1), true);
}
MPU::~MPU() {
	planManager.clearAll();
}

void MPU::run() {
	loadDefaultConfig();
}

void MPU::loadDefaultConfig() {
	json l = Utils::loadDefaultConfig();
	string missionPlan = l["mp"];
	std::ifstream file(missionPlan);
	json j;
	file >> j;
	loadPlan(j);
	file.close();
}

void MPU::handleUpdateConfig(json j) {
	json l = Utils::loadConfig(j);
	string missionPlan = l["mp"];
	std::ifstream file(missionPlan);
	json k;
	file >> k;
	loadPlan(k);
	file.close();
}

void MPU::loadPlan(json j) {
	plan = Utils::parsePlan(j);
	cout << "Sending: " << j << endl;
	sendPlan(j);
	MPU::planManager.add(plan->getId(), plan);
}

void MPU::sendPlan(const json &j) {
	MPU::amq.publish("updateMissionPlan", j, true);
}

void MPU::updateNewTasking(json j) {
	plan = Utils::parsePlan(j);
	MPU::planManager.add(plan->getId(), plan);
	sendPlan(j);
}
