#pragma once
#ifndef RDR_H
#define RDR_H

#include <missions/MissionPlan.h>
#include <nlohmann/json.hpp>
#include "Utils.h"
#include <amqm/AMQManager.h>
#include <Store.h>


using namespace std;
using namespace uas;
using namespace amqm;
using namespace std::placeholders;

using json = nlohmann::json;
class RDR {
public:
	RDR() {
		amq.listen("updateMissionPlan", std::bind(&RDR::handleNewPlan, this, _1), true);
	}

private:
	AMQManager amq;
	Store<MissionPlan *> *planManager = new Store<MissionPlan *>(5);
	void handleNewPlan(json j) {
		MissionPlan *plan = Utils::parsePlan(j);
		planManager->add(plan->getId(), plan);
	}
};
#endif
