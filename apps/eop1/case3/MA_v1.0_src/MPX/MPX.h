#pragma once
#ifndef MPX_H
#define MPX_H
#include <missions/MissionPlan.h>
#include <nlohmann/json.hpp>
#include <Store.h>
#include <missions/CommonUAS.h>
#include <unordered_set>
#include <string>
#include <amqm/AMQManager.h>
#include <atomic>
#include "TOI.h"

using namespace uas;
using namespace std;
using namespace amqm;
using json = nlohmann::json;
/**
* @brief – Class responsible for PNT updates, asset location calculation, current mission status,
* detection list collection from sensors manager (ISRM), generation of TOI list
*
* @author – Original Author - Mases Krikorian
* @author – Last Edited By - Frederick Santiago
* @date – 9/15/2020
*
* @details – This system starts execution when a mission plan is sent(from MPU)/loaded.
* Every 1 second, a new location is calculate based on the next waypoint and speed, and the 
* location is sent to all other systems. Additionally, it checks for current status of the mission
* and the phase to determine what data to request from ISRM. Once an action waypoint is reached, a request
* gets sent to ISRM for detections. The results are then retrieved back from ISRM. This list will get filtered
* and the output will be a TOI list.
* 
* @todo add favorable distance to TOI list detection filtering
*/
class MPX {
public:
	/**
	 * @brief Construct a new MPX object based on a mission plan, listen to mission plan changes and ISRM detections
	 * 
	 * @param plan - parsed from a mission plan JSON. Refer to Utils::parsePlan and MPU/mp.json
	 */
	MPX(MissionPlan *plan);
	/**
	 * @brief Construct a new MPX object and listen to mission plan changes and ISRM detections
	 * 
	 */
	MPX();
	/**
	 * @brief Destroy the MPX object and clear all storage for mission plans and detections
	 * 
	 */
	~MPX();
	/**
	 * @brief create two threads: one to check plan status and calculate PNT location and 
	 * the other to print useful debug information to the console
	 *
	 * @param VOID 
	 * 
	 * @return VOID
	 */
	void run();
	/**
	 * @brief updatet the plan manager with new plan and set it as current plan
	 * 
	 * @param plan - contains information about vehicle plan (waypoints), and sensor plan (actions at waypoints)
	 *
	 * @return VOID
	 */
	void updateMissionPlan(MissionPlan *plan);
	/**
	 * @brief indicate a change of plan to the system
	 * 
	 * @param c - if true, plan changed
	 *
	 * @return VOID
	 */
	void setChanged(const bool &c);
	/**
	 * @brief setter method for speed
	 *
	 * @param speed - contains the new speed
	 *
	 * @return VOID
	 */
	void setSpeed(double speed);
	/**
	 * @brief setter method for location
	 *
	 * @param lat - contains the new latitude
	 * @param lon - contains the new longitude
	 * @param alt - contains the new altitude
	 *
	 * @return VOID
	 */
	void setLocation(double lat, double lon, double alt);
	/**
	 * @brief print useful information about UAV location, phase, distance to next waypoint, elapsed time
	 *  bearing, plan id, speed, and location of next waypoint
	 * 
	 * @param VOID
	 *
	 * @return VOID
	 */
	void printInformation();
	/**
	 * @brieft Every 1 second, a new location is calculated based on the next waypoint and speed, and the 
	 * location is sent to all other systems as PNT. Additionally, it checks for current status of the mission
	 * and the phase to determine what data to request from ISRM. If at last waypoint, mission is considered complete
	 * 
	 * @param planManager - storage of all mission plans sent from MPU
	 *
	 * @return VOID
	 */
	void checkPlanStatus(Store<MissionPlan*> &planManager);

private:
	/**
	 * @brief update plan manager with a new copy of mission plan sent by MPU
	 * 
	 * @param j - refer to MPU/missionplans/MP-001.json for a sample
	 *
	 * @return VOID
	 */
	void handleNewPlan(json j);
	/**
	 * @brief process the default configuration content
	 *
	 * @param j - refer to MPX/config/defaultConfig.json for a sample
	 *
	 * @return VOID
	 */
	void processConfigDefaultContent(json j);
	/**
	 * @brief process the configuration content based on the configuration plan json
	 *
	 * @param j - refer to MPX/config/fly-low.json for a sample
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
	 * @brief based on the waypoint and the action attached to it (either FIND or FIX), request data
	 * from the sensor manager
	 * 
	 * @param phase - either "find" or "fix"
	 *
	 * @return VOID
	 */
	void requestISRMDetections(const string &phase);
	/**
	 * @brief passed to ActiveMQ Manager as a callback function. When data is sent from ISRM for detections, this
	 * function will be triggered. It will filter the detections and add them to a TOI list.
	 * 
	 * @param j - an array of objects, for each containining keys: "TGT_ISRM_ID": string,
	 * "lat": double, "lon": double, "alt", "speed": double, "bearing": double, "confidence": double,
	 *  and "classification": string. Confidence and classification will be -1 and empty respectively since
	 * that data comes from EOIR, and speed and bearing will be -1 during FIND phase.
	 *
	 * @return VOID
	 */
	void recieveISRMDetections(json j);
	/**
	 * @brief print all TOI from the TOIList store
	 *
	 * @param VOID
	 *
	 * @return VOID 
	 */
	void printTOIList();
	/**
     * @brief ActiveMQ Manager instance to listen and publish messages
     * 
    */
	AMQManager amq;
	/**
	 * @brief amount of time to sleep in ms
	 * 
	 * @todo this is unused?
	 */
	int sleep_msec = 1000;
	/**
	 * @brief timer to count time elapsed
	 * 
	 */
	time_t timer;
	/**
	 * @brief time in long when the system starts
	 * 
	 */
	long startTime = time(&timer);
	/**
	 * @brief Storage for all mission plans recieved from MPU
	 * 
	 */
	Store<MissionPlan*> planManager;
	/**
	 * @brief Storage for all detections recieved from ISRM and filtered
	 * 
	 */
	Store<TOI*> toiList;
	/**
	 * @brief current asset location
	 * 
	 */
	uas::Location location;
	/**
	 * @brief current schedule index
	 *
	 */
	int schedule = 0;
	/**
	 * @brief current asset speed in km/s
	 * 
	 * @todo this needs to be adjusted
	 */
	double speed;
	/**
	 * @brief minimum confidence to be considered in TOI list
	 * 
	 * @todo this is unused
	 */
	const double confidence = 0.4;
	/**
	 * @brief set of classifcaiton to be considered in TOIList
	 * 
	 * @todo implement this feature
	 */
	unordered_set<string> classifications;
	/**
	 * @brief current distance in km from next waypoint
	 * 
	 */
	double distance = 0;
	/**
	 * @brief current bearing towards the next waypoint in degrees
	 * 
	 */
	double bearing = 0;
	/**
	 * @brief true if plan has been changed
	 * 
	 */
	bool changed = false;
	/**
	 * @brief true if MPX has started FIND phase
	 * 
	 */
	bool findStarted = false;
	/**
	 * @brief true if MPX has started FIX phase
	 * 
	 */
	bool fixStarted = false;
	/**
	 * @brief for DEBUG: current phase represented in string
	 * 
	 */
	string phase = "N/A";
	/**
	 * @brief if true, mission execution thread will terminate
	 * 
	 */
	bool missionComplete = false;
	/**
	 * @brief if true, system thread will continue execution, if false, thread will terminate
	 * 
	 */
	std::atomic<bool> running;
};
#endif
