#pragma once
#ifndef MISSION_PLAN_H
#define MISSION_PLAN_H
#include <missions/Schedule.h>
#include <string>
#include <iostream>
#include <Store.h>
#include <tsl/ordered_map.h>

using namespace std;
using namespace uas;
namespace uas {
	/**
	* @brief – Class responsible for structure of a Mission Plan
	*
	* @author – Original Author - Mases Krikorian
	* @author – Last Edited By - Mases Krikorian
	* @date – 9/2/2020
	*
	* @details – maintains the strucutre of a mission plan, which include an id, a store (list) of waypoints (schedules) 
	* 
	*/
class MissionPlan {
public:
	/**
	 * @brief Construct a new Mission Plan object with a unique id and a max number of schedules a plan can have (50)
	 * 
	 * @param id - unique identification of the plan
	 * @param s - size of plan's waypoints
	 */
	MissionPlan(string id, int s) : schedules(50) {
		this->id = id;
		size = s;
	}
	/**
	 * @brief create a new schedule on the heap and add it to the plan 
	 * schedule store based on a waypoint id, and the location of the waypoint
	 * 
	 * @param wayPointId - unique identification
	 * @param x - x or lat (in degrees )value of waypoint 
	 * @param y - y or lat (in degrees )value of waypoint 
	 * @param z - z or lat (in degrees )value of waypoint 
	 *
	 * @return VOID
	 */
	void addSchedule(const string &wayPointId, double x, double y, double z) {
		Schedule *schedule = new Schedule(wayPointId, x, y, z);
		schedules.add(wayPointId, schedule);
	}
	/**
	 * @brief Get the Schedule object based on its index relative to the order of insertion
	 * 
	 * @param i - index of the schedule to retrieve
	 *
	 * @return Schedule* - pointer to the schedule retrieved, nullptr if not found
	 */
	Schedule* getSchedule(int i) {
		return schedules.get(i);
	}
	/**
	 * @brief Get the Schedule object
	 * 
	 * @param id - unique id of schedule retrieved from the ordered map
	 *
	 * @return Schedule*  pointer to the schedule retrieved, nullptr if not found
	 */
	Schedule* getSchedule(const string &id) {
		if (schedules.contains(id)) {
			return schedules.get(id);
		}
		return nullptr;
	}
	/**
	 * @brief Get the Head Schedule object
	 * 
	 * @param VOID
	 *
	 * @return Schedule* pointer to the last inserted schedule
	 */
	Schedule* getHeadSchedule() {
		return schedules.getHead();
	}
	/**
	 * @brief Remove the last inserted schedule 
	 * 
	 * @param VOID
	 *
	 * @return VOID
	 */
	void popSchedule() {
		schedules.removeHead();
	}
	/**
	 * @brief Get the Map object of the ordered-by-insertion list of waypoints
	 * 
	 * @param VOID
	 *
	 * @return tsl::ordered_map<string, Schedule*> map of the ordered-by-insertion list of waypoints
	 */
	tsl::ordered_map<string, Schedule*> getMap() {
		return schedules.getMap();
	}
	/**
	 * @brief Get the Id object
	 * 
	 * @param VOID
	 *
	 * @return string& id of the mission plan
	 */
	string& getId() {
		return id;
	}
	/**
	 * @brief Print the last-inserted plan's id, next waypoint
	 * 
	 * @param VOID
	 * 
	 * @return VOID
	 */
	void printInformation() {
		cout << "ID: " << schedules.getHead()->getId() << endl;;
		cout << "Next Waypoint: [" << "lat: " << schedules.getHead()->getX() << ", lon: " <<
			schedules.getHead()->getY() << ", alt: " << schedules.getHead()->getY() << "]" << endl;
	}
	/**
	 * @brief Get the Schedule Size object
	 * 
	 * @param VOID
	 * 
	 * @return int schedule of the number of waypoints
	 */
	int getScheduleSize() {
		return size;
	}
	/**
	 * @brief Destroy the Mission Plan object and clear the schedules storage
	 * 
	 */
	~MissionPlan() {
		schedules.clearAll();
	}
private:
	/**
	 * @brief Unique mission plan id
	 * 
	 */
	string id;
	/**
	 * @brief Store, ordered map, of schedules ordered by insertion
	 * 
	 */
	Store<Schedule*> schedules;
	/**
	 * @brief Size of waypoints (schedules) store
	 * 
	 */
	int size;
	
};
}
#endif