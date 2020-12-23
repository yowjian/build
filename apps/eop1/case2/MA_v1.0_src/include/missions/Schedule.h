#pragma once
#ifndef SCHEDULE_H
#define SCHEDULE_H
#include <string>
#include <missions/CommonUAS.h>
using namespace std;
using namespace uas;
/**
 * @brief Phase attached to each waypoint
 * 
 */
enum Phase {FIND, FIX, TRACK, TARGET, NONE};
namespace uas {
/**
 * @brief Waypoint structure which consisnt of location
 * 
 */
struct Waypoint {
	/// required empty constructor
	Waypoint() {

	}
	/// constructor with x, y, z for lat, lon, alt
	Waypoint(double x, double y, double z) {
		loc.x = x;
		loc.y = y;
		loc.z = z;
	}
	/// uas::Location
	Location loc;

};

	/**
	* @brief – Class responsible for structure of a Schedule (waypoint)
	*
	* @author – Original Author - Mases Krikorian
	* @author – Last Edited By - Mases Krikorian
	* @date – 9/2/2020
	*
	* @details – maintains the strucutre of a waypoint, which includes location, waypoint id, action phase, 
	* and whether it's an egress point 
	* 
	*/
class Schedule {
public:
	/**
	 * @brief Construct a new Schedule object with location parameters
	 * 
	 * @param pid - unique id of the schedule (waypoint)
	 * @param x - x/lat (in degrees) value of schedule
	 * @param y - y/lon (in degrees) value of schedule
	 * @param z - z/alt (in degrees)  value of schedule
	 */
	Schedule(string pid, double x, double y, double z) {
		id = pid;
		waypoint.loc.x = x;
		waypoint.loc.y = y;
		waypoint.loc.z = z;
	}
	/**
	 * @brief Construct a new Schedule object, required for empty schedule instances
	 * 
	 */
	Schedule() {}
	/**
	 * @brief Set the Data of the waypoint after empty initialization
	 * 
	 * @param pid - unique id of the schedule (waypoint)
	 * @param x - x/lat (in degrees) value of schedule
	 * @param y - y/lon (in degrees) value of schedule
	 * @param z - z/alt (in degrees)  value of schedule
	 *
	 * @return VOID
	 */
	void setData(string pid, double x, double y, double z) {
		id = pid;
		waypoint.loc.x = x;
		waypoint.loc.y = y;
		waypoint.loc.z = z;
	}
	/**
	 * @brief get x/lat value of the schedule
	 *
	 * @param VOID
	 * 
	 * @return double x/lat value in degrees
	 */
	double getX() {
		return (waypoint.loc.x);
	}
	/**
	 * @brief get y/lat value of the schedule
	 *
	 * @param VOID
	 * 
	 * @return double y/lat value in degrees
	 */
	double getY() {
		return (waypoint.loc.y);
	}
	/**
	 * @brief get z/alt value of the schedule
	 *
	 * @param VOID
	 * 
	 * @return double z/alt value in degrees
	 */
	double getZ() {
		return (waypoint.loc.z);
	}
	/**
	 * @brief Get the Id of the schedule
	 * 
	 * @param VOID
	 *
	 * @return string& referrence to the id
	 */
	string& getId() {
		return id;
	}
	/**
	 * @brief Set the Phase to one of the Phase enum value based on string
	 * input. string can be "find", "fix", "track", or "target" 
	 * If none of those is passed, NONE will be used 
	 * 
	 * @param phase - "find", "fix", "track", or "target" 
	 *
	 * @return VOID
	 */
	void setPhase(const string &phase) {
		if (phase == "find") {
			p = Phase::FIND;
		}
		else if (phase == "fix") {
			p = Phase::FIX;
		}
		else if (phase == "track") {
			p = Phase::TRACK;
		}
		else if (phase == "target") {
			p = Phase::TARGET;
		}
		else {
			p = Phase::NONE;
		}
	}
	/**
	 * @brief Get the Phase of the waypoint
	 * 
	 * @param VOID
	 *
	 * @return string - "find", "fix", "track", "target", or "N/A" 
	 */
	string getPhase() {
		switch (p) {
		case FIND:
			return "find";
		case FIX:
			return "fix";
		case TRACK:
			return "track";
		case TARGET:
			return "target";
		default:
			return "N/A";
		}
	}
	/**
	 * @brief 
	 * 
	 * @param
	 *
	 * @return true if waypoint is the last in the waypoint store
	 */
	bool isEgressPoint() {
		return egressPoint;
	}
	/**
	 * @brief Set the Egress Point when the plan is recieved and created. Only last schedule 
	 * will set this to true
	 * 
	 * @param egressPoint 
	 */
	void setEgressPoint(bool egressPoint) {
		this->egressPoint = egressPoint;
	}
private:
	/**
	 * @brief unique id of the schedule
	 * 
	 */
	string id;
	/**
	 * @brief Waypoint, or location represented with lat, lon, alt
	 * 
	 */
	Waypoint waypoint;
	/**
	 * @brief Phase enum value of the schedule. NONE by default.
	 * 
	 */
	Phase p = NONE;
	/**
	 * @brief true if the schedule is the last point. False by default.
	 * 
	 */
	bool egressPoint = false;

};
}
#endif
