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

    /**
     * @brief
     *
     * @param j - The json message containing the image
     *
     * @return VOID
     */
	void updateImageDetected(const json &j);

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
