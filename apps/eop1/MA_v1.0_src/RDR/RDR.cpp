#include <iostream>
#include <fstream>
#include "RDR.h"
#include "Utils.h"
#include <thread>


using namespace std;
using namespace std::placeholders;

RDR::RDR() : planManager(5), detections(20) {
	ended = false;
	amq.listen("updateMissionPlan", std::bind(&RDR::handleNewPlan, this, _1), true);
	amq.listen("pnt", std::bind(&RDR::handleLocation, this, _1), true);
	amq.listen("groundMovers", std::bind(&RDR::handleGroundMovers, this, _1), true);
	amq.listen("requestRDRDetections", std::bind(&RDR::handleRequestRDRDetections, this, _1), true);
	amq.listen("updateConfig", std::bind(&RDR::handleUpdateConfig, this, _1), true);
	json j = Utils::loadDefaultConfig();
	processConfigContent(j);
}

void RDR::processConfigContent(json j) {
	detections.setSize(j["maxDetects"]);
}

void RDR::handleUpdateConfig(json j) {
	json k = Utils::loadConfig(j);
	processConfigContent(k);
}

RDR::~RDR() {
	ended = true;
	planManager.clearAll();
	Utils::sleep_for(1000);

}
void RDR::run() {
	std::thread t1 = std::thread(&RDR::checkPlanStatus, this, std::ref(planManager), std::ref(loc));
	t1.detach();
}

void RDR::checkPlanStatus(Store<MissionPlan *> &planManager, Location &loc) {
	while (ended) {
		if (planManager.getCurrent() != nullptr) {
			Schedule *schedule = RDR::nearWayPoint(planManager, loc);
			if (schedule != nullptr) {
				if (schedule->isEgressPoint()) {
					break;
				}
			}
		}
		Utils::sleep_for(1000);
	}
}
void RDR::handleLocation(json j) {
	loc.x = j["lat"];
	loc.y = j["lon"];
	loc.z = j["alt"];
	nearWayPoint(planManager, loc);

}
Schedule* RDR::nearWayPoint(Store<MissionPlan *> &planManager, Location &loc) {
	for (const auto& key_value : planManager.getCurrent()->getMap()) {
		double d = Utils::distanceEarth(loc.x, loc.y, key_value.second->getX(), key_value.second->getY());
		if (Utils::isNear(d, 0.5)) {
			return key_value.second;
		}
	}
	return nullptr;
}



void RDR::handleNewPlan(json j) {
	MissionPlan *plan = Utils::parsePlan(j);
	planManager.add(plan->getId(), plan);
}

void RDR::handleRequestRDRDetections(json j) {
	json resp = json::array();
	json body;
	if (j["phase"] == "find") {
		for (auto key_value : detections.getMap()) {
			body["TGT_ISRM_ID"] = key_value.second->getId();
			body["lat"] = key_value.second->getLat();
			body["lon"] = key_value.second->getLon();
			body["alt"] = key_value.second->getAlt();
			body["bearing"] = -1.0;
			body["speed"] = -1.0;
			body["confidence"] = key_value.second->getConfidence();
			body["classification"] = key_value.second->getClassification();
			resp.push_back(body);
			body.clear();
		}
	}
	else if (j["phase"] == "fix") {
		for (auto key_value : detections.getMap()) {
			body["TGT_ISRM_ID"] = key_value.second->getId();
			body["lat"] = key_value.second->getLat();
			body["lon"] = key_value.second->getLon();
			body["alt"] = key_value.second->getAlt();
			body["bearing"] = key_value.second->getBearing();
			body["speed"] = key_value.second->getSpeed();
			body["confidence"] = key_value.second->getConfidence();
			body["classification"] = key_value.second->getClassification();
			resp.push_back(body);
			body.clear();
		}
	}
	amq.publish("recieveRDRDetections", resp, true);
}



void RDR::handleGroundMovers(json j) {
	string id =j["vehicleID"];
	if (detections.contains(id)) {
		detections.get(id)->setLocation(j["lat"], j["lon"], 0);
		detections.get(id)->setSpeed(j["speed"]);
		detections.get(id)->setBearing(j["bearing"]);
	}
	else {
		Detect *detect = new Detect(j["lat"], j["lon"], 0.0, id, j["speed"], j["bearing"]);
		detections.add(id, detect);
	}
}