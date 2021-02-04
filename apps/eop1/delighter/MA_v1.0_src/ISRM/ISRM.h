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

class ISRM {
public:
	ISRM();

	~ISRM();

	void run();

	void handleRecieveISRMDetectionsXD(json j);

private:

	/**
     * @brief ActiveMQ Manager instance to listen and publish messages
     * 
    */
	AMQManager amq;

	string imageDir;

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
