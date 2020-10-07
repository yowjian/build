#pragma once
#ifndef ISRMPLAN_H
#define ISRMPLAN_H
#include <missions/MissionPlan.h>
#include <nlohmann/json.hpp>
#include <Store.h>
using namespace uas;
using json = nlohmann::json;

struct SensorAction {
	SensorAction(){}
	SensorAction(string actionId, string wayPointId, Phase phase) {
		this->actiondId = actiondId;
		this->wayPointId = wayPointId;
		this->phase = phase;
	}
	string actiondId;
	string wayPointId;
	Phase phase;

};
class ISRMPlan : public MissionPlan {
public:
	ISRMPlan(string id, int s) : MissionPlan(id, s) {

	}
	~ISRMPlan() {
		sensorActions->clearAll();
		delete sensorActions;
	}
	void parseSensorPlanAndUpdate(json j) {
		sensorActions = new Store<SensorAction*>(50);
		json actionsArr = j["missionPlan"]["sensorPlan"]["actions"];
		SensorAction *act = new SensorAction(actionsArr[0]["actionId"], actionsArr[0]["wayPointId"], FIND);
		for (int i = 0; i < actionsArr.size(); i++) {
			sensorActions->add(actionsArr[0]["actionId"], act);
		}
	}
private:
	Store<SensorAction*> *sensorActions;
	


};
#endif
