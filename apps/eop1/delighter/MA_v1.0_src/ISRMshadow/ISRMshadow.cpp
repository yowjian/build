
#include <stdio.h>
#include <string>
#include <fstream>
#include <amqm/AMQManager.h>
#include <Utils.h>
#include "ISRMshadow.h"

using namespace amqm;
using namespace cms;
using namespace std;

ISRMShadow::ISRMShadow() {
	amq.listen("imageDetected", std::bind(&ISRMShadow::updateImageDetected, this, _1), true);

	json j = Utils::loadDefaultConfig();
	processConfigContent(j);
}

void ISRMShadow::processConfigContent(json j) {
}

ISRMShadow::~ISRMShadow() {
}

void ISRMShadow::run() {

}

void ISRMShadow::updateImageDetected(const json &j) {
    cout << "ISRMshadow received imageDetected" << endl;
//	MissionPlan *plan = Utils::parsePlan(j);
//	planManager.add(plan->getId(), plan);
//
//        // WARNING: risk of infinite loop if ISRMshadow run on same side as ISRM
//	ISRMShadow::amq.publish("updateMissionPlan", j, true);
}
