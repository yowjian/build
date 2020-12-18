#pragma once
#ifndef RDR_H
#define RDR_H
#include <missions/MissionPlan.h>
#include <nlohmann/json.hpp>
#include <amqm/AMQManager.h>
#include <string>
#include <Store.h>
#include <missions/Detect.h>
#include <atomic>

using namespace std;
using namespace amqm;
using namespace uas;


/**
* @brief – Class responsible for saving and updating ground movers as sensor detections
* and returning results to sensor manager (ISRM)
*
* @author – Original Author - Mases Krikorian
* @author – Last Edited By - Frederic Santiago
* @date – 9/15/2020
*
* @details – Class responsible for saving and updating ground movers as sensor detections
* and returning results to sensor manager (ISRM)
*/
class RDR {
public:
	/**
	 * @brief Construct a new RDR object and set listeners for 
	 * detection requests ,mission plan changes, current UAV position, and ground movers updates
	 * 
	 */
	RDR();
	/**
	 * @brief Destroy the RDR object and empty the storage
	 * 
	 */
	~RDR();
	/**
	 * @brief recieve the request from ISRM for new detections. 
	 * 
	 * @param j - contains key "phase" which can be either "find" or "fix"
	 *
	 * @return VOID 
	 */
	void handleRequestRDRDetections(json j);
	/**
	 * @brief start a thread to check actions corresponding to current location recieved from PNT 
	 *
	 * @param VOID
	 *
	 * @return VOID
	 */
	void run();
private:
    /**
     * @brief ActiveMQ Manager instance to listen and publish messages
     * 
    */
	AMQManager amq;
	/**
	 * @brief Storage for all mission plans recieved from MPU
	 * 
	 */
	Store<MissionPlan *> planManager;
	/**
	 * @brief Storage for all detections recieved from RDR Sensor (simulated by Ground Movers)
	 * 
	 */
	Store<Detect *> detections;
	/**
	 * @brief Current location of asset
	 * 
	 */
	Location loc;
	/**
	 * @brief Using current plan's waypoints to check if current location is near
	 * a radar action
	 * 
	 * @param planManager - contains all copies of mission plans sent by MPU
	 * @param loc - current location of asset
	 * 
	 * @return VOID
	 */
	void checkPlanStatus(Store<MissionPlan *> &planManager, Location &loc);
	/**
	 * @brief update asset's current location sent from PNT
	 * 
	 * @param j contains keys "lat": double, "lon": "double", "alt": double, "time": string
	 *
	 * @return vOID
	 */
	void handleLocation(json j);
	/**
	 * @brief check if asset is near a waypoint from all the waypoints available in the plan
	 * 
	 * @param planManager - reference to storage that contains all mission plans sent by MPU
	 * @param loc - reference to current location of asset
	 *
	 * @return Schedule* - pointer to a Schedule that exists inside a current plan's 
	 * waypoint storage that is within a certain range of our current location
	 *
	 * @todo Make this function a shared function for all systems in Utils,
	 * only check the first waypoint, if we are near it, signal the system and 
	 * pop it off the waypoint list.
	 */
	Schedule* nearWayPoint(Store<MissionPlan *> &planManager, Location &loc);
	/**
	 * @brief update plan manager with a new copy of mission plan sent by MPU
	 * 
	 * @param j - refer to MPU/missionplans/MP-001.json for a sample
	 *
	 * @return VOID
	 */
	void handleNewPlan(json j);
	/**
	 * @brief update detections store with update or new information about the ground movers
	 * (radar detections)
	 * 
	 * @param j - an array of objects, for each containining keys: "vehicleID": string,
	 * "lat": double, "lon": double, "alt", "speed": double, "bearing": double
	 *
	 * @return VOID
	 */
	void handleGroundMovers(json j);
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
	 * @brief shared boolean that tells RDR to start or stop running
	 * 
	 */
	std::atomic<bool> ended;
	/**
	 * @brief true if RDR has started FIND phase
	 * 
	 */
	bool findStarted = false;
	/**
	 * @brief true if RDR has started FIX phase
	 * 
	 */
	bool fixStarted = false;
};
#endif
