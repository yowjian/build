#pragma once
#ifndef MPU_H
#define MPU_H
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
# include <Windows.h>
#else
# include <unistd.h>
#endif
#include "Store.h";
#include <missions/MissionPlan.h>
#include <Utils.h>
#include <fstream>
#include <iostream>
#include <amqm/AMQManager.h>
#include <functional>

using namespace std;
using namespace uas;
using namespace amqm;
using namespace std::placeholders;

class MPU {
public:
	MPU() {
		amq.listen("updateNewTasking", std::bind(&MPU::updateNewTasking, this, _1), true);
	}
	void loadPlan() {
		std::ifstream i("mp.json");
		json j;
		i >> j;
		plan = Utils::parsePlan(j);
#ifdef _WIN32	  
		Sleep(sleep_msec); // 100 Hz
#else
		usleep(sleep_msec * 1000);

#endif
		cout << "Sending: " << j << endl;
		sendPlan(j);
		planManager->add(plan->getId(), plan);
	}

private:
	AMQManager amq;
	void sendPlan(const json &j) {
		amq.publish("updateMissionPlan", j, true);
	}
	void updateNewTasking(json j) {
		plan = Utils::parsePlan(j);
		planManager->add(plan->getId(), plan);
	}
	int sleep_msec = 1000;
	MissionPlan *plan;
	Store<MissionPlan*> *planManager = new Store<MissionPlan*>(5);
};
#endif
