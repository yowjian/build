#ifndef NOMINMAX
# define NOMINMAX
#endif
#include <nlohmann/json.hpp>
#include <tsl/ordered_map.h>
#include <missions/MissionPlan.h>
#include <iostream>
#include <fstream>
#include <Utils.h>
#include "EOIR.h"


using namespace std;
using namespace uas;
 

EOIR::EOIR() : planManager(5), detects(20) {
	amq.listen("updateMissionPlan", std::bind(&EOIR::updateMissionPlan, this, _1), true);
	amq.listen("requestEOIRDetections", std::bind(&EOIR::handleRequestEOIRDetections, this, _1), true);
	amq.listen("groundMovers", std::bind(&EOIR::handleGroundMovers, this, _1), true);
	amq.listen("updateConfig", std::bind(&EOIR::handleUpdateConfig, this, _1), true);
	json j = Utils::loadDefaultConfig();
	processConfigContent(j);
	gapsOpenCV.init();
}

void EOIR::processConfigContent(json j) {
	detects.setSize(j["maxDetects"]);
}

void EOIR::handleUpdateConfig(json j) {
    Utils::logElapsedTime(j, "EOIR", "updateConfig");

	json k = Utils::loadConfig(j);
	processConfigContent(k);
}

EOIR::~EOIR() {
	planManager.clearAll();
	detects.clearAll();
}

void EOIR::run() {
	gapsOpenCV.run();
}

void EOIR::updateMissionPlan(json j) {
    Utils::logElapsedTime(j, "EOIR", "updateMissionPlan");

	MissionPlan *plan = Utils::parsePlan(j);
	planManager.add(plan->getId(), plan);
}


void EOIR::handleRequestEOIRDetections(json j) {
    Utils::logElapsedTime(j, "EOIR", "requestEOIRDetections");

	while (gapsOpenCV.isRunning()) {
		Utils::sleep_for(500);
	}
	int i = 0;
	for (const auto &it : gapsOpenCV.getMap()) {
		detects.get(i)->setClassification(it.second.classification);
		detects.get(i)->setConfidence(it.second.confidence);
		i++;
		if (i >= detects.size()) {
			break;
		}
	}
	json resp = json::array();
	json body;
	if (j["phase"] == "find") {
		for (auto key_value : detects.getMap()) {
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
		for (auto key_value : detects.getMap()) {
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
	json j1;
	j1["detects"] = resp;
	amq.publish("recieveEOIRDetections", j1, true);
	
}

void EOIR::handleGroundMovers(json j) {
    Utils::logElapsedTime(j, "EOIR", "groundMovers");

	string id = j["vehicleID"];
	if (detects.contains(id)) {
		detects.get(id)->setLocation(j["lat"], j["lon"], 0);
		detects.get(id)->setSpeed(j["speed"]);
		detects.get(id)->setBearing(j["bearing"]);
	}
	else {
		Detect *detect = new Detect(j["lat"], j["lon"], 0.0, id, j["speed"], j["bearing"]);
		detects.add(id, detect);
	}
}
