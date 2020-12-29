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

/**
* @brief – Class responsible for managing, collobrating, and directing on-board sensor packages
* 
*
* @author – Original Author - Mases Krikorian
* @author – Last Edited By - Frederick Santiago
* @date – 9/15/2020
*
* @details – When all the systems are ready, ISRM will load the flight plan and request collections from the various
* sesnors.
*
* 
* @todo implement EOIR/RDR correlation
*/

class ISRM {
public:
	/**
	 * @brief Construct a new ISRM object
	 *
	 * @param int - The number of collections you wish to define as the maximum the ISRM object will hold
	 * 
	 */
	ISRM(int);
	/**
	 * @brief Destroy the ISRM object and clear all collection storage
	 * 
	 */
	~ISRM();
	/**
	 * @brief Function Stub
	 * 
	 */
	void run();
	/**
	 * @brief Function Stub
	 * 
	 *
	 * @return VOID
	 */
	void classify();
	/**
	 * @brief Display sensor returns in console
	 * 
	 *
	 * @return VOID
	 */
	void print();
	/**
	 * @brief Mock function that creates two detects and then "correlates" them
	 * 
	 *
	 * @return VOID
	 */
	void collectDetects();
	/**
	 * @brief Mock function adds speed and bearing to a detection
	 * 
	 *
	 * @return VOID
	 */
	void appendMoreData();
	/**
	 * @brief Function Stub
	 * 
	 *
	 * @return VOID
	 */
	void collectTRACK();
	/**
	 * @brief Compared to detects to see if they are same via IDs and location
	 * 
	 * @param id1 - the ID String name of the first detection you wish to compare
	 *
	 * @param id2 - the ID String name of the second detection you wish to compare
	 *
	 * @return VOID
	 */
	void correlate(const string& id1, const string& id2);
	/**
	 * @brief Handles ActiveMQ request for requets from MPU, sends requests via ActiveMQ to sensor subsystems
	 * 
	 * @param j - The json message containing the phase for the request
	 *
	 * @return VOID
	 */
	void handleDetectionsRequest(json j);

	void handleRecieveISRMDetectionsXD(json j);

	/**
	 * @brief Handles ActiveMQ response from EOIR for detects
	 * 
	 * @param j - The json message containing any detections the EOIR has recorded
	 *
	 * @return VOID
	 */
	void handleRecieveEOIRDetections(json j);
	/**
	 * @brief Function Stub
	 * 
	 *
	 * @return VOID
	 */
	void EOBU();
	/**
	 * @brief Function Stub
	 * 
	 *
	 * @return VOID
	 */
	void FLTR();
	/**
	 * @brief Function Stub
	 * 
	 *
	 * @return VOID
	 */
	void geoLOC();
	/**
	 * @brief Function Stub
	 * 
	 *
	 * @return VOID
	 */
	void ID();
	/**
	 * @brief Function Stub
	 * 
	 *
	 * @return VOID
	 */
	void SCHED();
	/**
	 * @brief Function Stub
	 * 
	 *
	 * @return VOID
	 */
	void SEL();
	/**
	 * @brief Function Stub
	 * 
	 *
	 * @return VOID
	 */
	void SenC2();
	/**
	 * @brief Function Stub
	 * 
	 *
	 * @return VOID
	 */
	void SenCollect();
	/**
	 * @brief Function Stub
	 * 
	 *
	 * @return VOID
	 */
	void SenMetaData();
	/**
	 * @brief Function Stub
	 * 
	 *
	 * @return VOID
	 */
	void SenPU();
	/**
	 * @brief Function Stub
	 * 
	 *
	 * @return VOID
	 */
	void TRKCOR();


private:
	/**
	 * @brief Storage for all detections recieved from ISRM/RDR
	 * 
	 */
	Store<Detect*> detects;
	/**
	 * @brief Storage for all mission plans recieved from MPU
	 * 
	 */
	Store<MissionPlan*> planManager;
	/**
     * @brief ActiveMQ Manager instance to listen and publish messages
     * 
    */
	AMQManager amq;
	/**
     * @brief Boolean value to keep track if RDR has successfully returned a message after a request has been made
	 *
    */
	bool rdrDataCollected = false;
	/**
     * @brief Boolean value to keep track if EOIR has successfully returned a message after a request has been made
	 *
    */
	bool eoirDataCollected = false;
	/**
	 * @brief Parses and stores any new mission plans that are sent out from the MPU
	 * 
	 * @param j - The json message containing the new plan
	 *
	 * @return VOID
	 */
	void updateMissionPlan(const json &j);
	/**
	 * @brief Handles ActiveMQ response from RDR for detects
	 * 
	 * @param j - The json message containing any detections the RDR has recorded
	 *
	 * @return VOID
	 */
	void handleRecieveRDRDetections(json j);
	/**
	 * @brief process the configuration content based on the configuration plan json
	 *
	 * @param j - refer to RDR/config/fly-low.json for a sample
	 *
	 * @return VOID
	 */
	void processConfigContent(json j);
	/**
	 * @brief handle a new configuration plan
	 *
	 * @param j - input json will follow {"configurationPlan" : *configuration plan string*} format
	 *
	 * @return VOID
	 */
	void handleUpdateConfig(json j);
};
#endif
