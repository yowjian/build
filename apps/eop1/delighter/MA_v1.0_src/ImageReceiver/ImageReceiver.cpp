
#include <stdio.h>
#include <string>
#include <fstream>
#include <amqm/AMQManager.h>
#include <Utils.h>
#include "ImageReceiver.h"

using namespace amqm;
using namespace cms;
using namespace std;

ImageReceiver::ImageReceiver() {
	amq.listen("imageDetected", std::bind(&ImageReceiver::updateImageDetected, this, _1), true);

	json j = Utils::loadDefaultConfig();
	processConfigContent(j);
}

void ImageReceiver::processConfigContent(json j) {
}

ImageReceiver::~ImageReceiver() {
}

void ImageReceiver::run() {

}

void ImageReceiver::updateImageDetected(const json &j) {
    cout << "ImageReceiver received imageDetected" << endl;
//	MissionPlan *plan = Utils::parsePlan(j);
//	planManager.add(plan->getId(), plan);
//
//        // WARNING: risk of infinite loop if ISRMshadow run on same side as ISRM
//	ISRMShadow::amq.publish("updateMissionPlan", j, true);
}
