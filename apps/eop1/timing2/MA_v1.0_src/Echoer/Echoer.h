#pragma once
#ifndef ISRM_H
#define ISRM_H
#include <Store.h>
#include <missions/Detect.h>
#include <string>
#include <missions/MissionPlan.h>
#include <amqm/AMQManager.h>
#include <nlohmann/json.hpp>

using namespace amqm;
using namespace uas;
using namespace std::placeholders;
using json = nlohmann::json;

class Echoer {
public:

	Echoer();

	~Echoer();

	void run();

private:
	AMQManager amq;

	void echo_component_heartbeats(const json &j);
	void echo_updateMissionPlan(const json &j);
	void echo_recieveISRMDetections(const json &j);
	void echo_groundMovers(const json &j);
	void echo_requestISRMDetections(const json &j);
	void echo_pnt(const json &j);
	void echo_requestEOIRDetections(const json &j);
	void echo_requestRDRDetections(const json &j);
	void echo_recieveEOIRDetections(const json &j);
	void echo_recieveRDRDetections(const json &j);

	/**
	 * @brief process the configuration content based on the configuration plan json
	 *
	 * @param j - refer to ISRM/config/defaultConfig.json for a sample
	 *
	 * @return VOID
	 */
	void processConfigContent(json j);

};
#endif
