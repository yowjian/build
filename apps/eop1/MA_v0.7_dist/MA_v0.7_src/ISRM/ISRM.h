#pragma once
#ifndef ISRM_H
#define ISRM_H
#include <Store.h>
#include "ISRMPlan.h"
#include "Detect.h"
#include <string>
#include <math.h>
#include <missions/MissionPlan.h>
#include <amqm/AMQManager.h>
#include <nlohmann/json.hpp>
#include <Utils.h>
#include "ISRM_Find_Fix.h"
#include "ISRMPlan.h"


using namespace amqm;
using namespace uas;
using namespace std::placeholders;
using json = nlohmann::json;

class ISRM {
public:
	ISRM(int maxDetects) {
		detects = new Store<Detect*>(maxDetects);
		planManager = new Store<ISRMPlan*>(5);
		amq.listen("updateMissionPlan", std::bind(&ISRM::updateMissionPlan, this, _1), true);
		amq.listen("requestISRMDetections", std::bind(&ISRM::handleDetectionsRequest, this, _1), true);
		collectDetects();
	}
	void classify() {
	}
	void print() {
		for (const auto& key_value : detects->getMap()) {
			cout << "id: " << key_value.first << endl;
			cout << "lat: " << key_value.second->getLat() << endl;
			cout << "lon: " << key_value.second->getLon() << endl;
			cout << "alt: " << key_value.second->getAlt() << endl;
			cout << "classification: " <<key_value.second->getClassification() << endl;
			cout << "speed: " << key_value.second->getSpeed() << endl;
			cout << "bearing: " << key_value.second->getBearing() << endl;
			cout << "***********" << endl;
		}
	}
	void collectDetects() {

		Detect *eoirDet1 = new Detect(0,0,0);
		eoirDet1->setClassification("tank");
		eoirDet1->setConfidence(0.7);


		Detect *rdrDet1 = new Detect(0.01,0.01,0.01);
		Detect *det2 = new Detect(1,1,1);
		rdrDet1->setConfidence(0.8);

		det2->setConfidence(0.9);
		det2->setClassification("bird");

 		detects->add("det1", eoirDet1);
		detects->add("det2", rdrDet1);
		detects->add("det3", det2);
		print();
		cout << "\n-------CORRELATING-------\n" << endl;
		correlate("det1", "det2");
		correlate("det2", "det3");
		correlate("det1", "det3");
		print();
	}

	void appendMoreData() {
		if (detects->contains("det2")) {
			Detect *detect = detects->get("det2");
			detect->setSpeed(1.2);
			detect->setBearing(0.7);
		}
	}
	void collectTRACK();
	void correlate(const string& id1, const string& id2) {
		if (detects->contains(id1) && detects->contains(id2)) {
				Detect *d1 = detects->get(id1);
				Detect *d2 = detects->get(id2);
				if ((std::ceil(d2->getLon() - 0.01 * 100.0) / 100.0) ==
					d1->getLon()) {
					
					d2->setClassification(d1->getClassification());
					delete detects->remove(id1);
				}
		}
	}

	void handleDetectionsRequest(json j) {
		//return detections by adding properties to det here
		string phase = j["phase"];
		json det;
		if (phase == "fix") {
			det = ISRM_Test_Data.send_Fix_Level_Detail();
		}
		else {
			det = ISRM_Test_Data.send_Find_Level_Detail();
		}
		amq.publish("recieveISRMDetections", det, true);
	}


	void EOBU();
	void FLTR();
	void geoLOC();
	void ID();
	void SCHED();
	void SEL();
	void SenC2();
	void SenCollect();
	void SenMetaData();
	void SenPU();
	void TRKCOR();


private:
	Store<Detect*> *detects;
	Store<ISRMPlan*> *planManager;
	AMQManager amq;
    ISRM_Data ISRM_Test_Data;
	void updateMissionPlan(json j) {
		ISRMPlan *plan = static_cast<ISRMPlan*>(Utils::parsePlan(j));
		plan->parseSensorPlanAndUpdate(j);
		planManager->add(plan->getId(), plan);
	}
};
#endif