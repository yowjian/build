#pragma once
#ifndef EOIR_H
#define EOIR_H
#include <chrono>
#include <missions/MissionPlan.h>
#include <thread>
#include <iostream>
#include <time.h>
#include <fstream>
#include <missions/CommonUAS.h>
#include <amqm/AMQManager.h>
#include <vector>
#include <Store.h>
#include <Utils.h>
#include "GAPS_openCV_Manager.h"

using namespace std;
using namespace amqm;
using namespace std::placeholders;

/**
* @brief – Class responsible for processing (and possibly generating)
* video input to OpenCV and storing the detections; awaiting for a 
* request from the sensor manager for detections and returning them.
* 
*
* @author – Original Author - OpenCV Dev Team
* @author – Last Edited By - Frederick Santiago
* @date – 9/15/2020
*
* @details – EOIR currently starts processing a video file that comes
* with the package. It stores the detections and awaits a request
* from the sensor manager (ISRM) for detections and combines the data from
* ground movers; adding the finding from the video (classification and confidence)
* to the detection list and sending it back to ISRM
*/
class EOIR {
public:
	/**
	 * @brief Construct a new EOIR object, listen for mission plan updates,
	 * requests for detections, and updates about ground mvoers. Initialize OpenCV library
	 * to process video input and generate the deep neural network model object.
	 * 
	 */
	EOIR();
	/**
	 * @brief Destroy the EOIR object, clear detects, clear plan manager
	 * 
	 */
	~EOIR();
	/**
	 * @brief Run the OpenCV library
	 * 
	 */
	void run();
private:
	/**
	 * @brief ActiveMQ handler for a new mission plan from MPU
	 * 
	 * @param j - refer to MPU/missionplans/MP-001.json for a sample
	 */
	void updateMissionPlan(json j);
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
	/**
	 * @brief Handle request from ISRM for list of detections
	 * and sending back the data to ISRM through recieveEOIRDetections
	 * 
	 * @param j - includes key "phase" with value being "find" or "fix"
	 * 
	 * @return VOID
	 */
	void handleRequestEOIRDetections(json j);
	/**
	 * @brief Update the list of detections with the updated location
	 * from ground movers 
	 * 
	 * @param j - an array of objects, for each containining keys: "vehicleID": string,
	 * "lat": double, "lon": double, "alt", "speed": double, "bearing": double
	 *
	 * @return VOID
	 */
	void handleGroundMovers(json j);
	/**
	 * @brief current location of asset
	 * 
	 */
	uas::Location currLoc;
	/**
	 * @brief time to sleep threads
	 * 
	 */
	int sleep_msec = 1000;
	/**
     * @brief ActiveMQ Manager instance to listen and publish messages
     * 
    */
	AMQManager amq;
	/**
	 * @brief Storage for all mission plans recieved from MPU
	 * 
	 */
	Store<MissionPlan*> planManager;
	/**
	 * @brief Storage for all detections recieved from Ground Movers
	 * 
	 */
	Store<Detect* > detects;
	/**
	 * @brief GAPS modified OpenCV library 
	 * 
	 */
	GAPS_openCV gapsOpenCV;

};
#endif