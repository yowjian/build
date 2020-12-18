#pragma once
#ifndef MISSION_PLAN_H
#define MISSION_PLAN_H
#include <missions/Schedule.h>
#include <string>
#include <iostream>
#include <Store.h>

using namespace std;
using namespace uas;
namespace uas {
class MissionPlan {
public:
	MissionPlan(string id, int s) : schedules(50) {
		size = s;
	}

	void addSchedule(const string &wayPointId, double x, double y, double z) {
		Schedule *schedule = new Schedule(wayPointId, x, y, z);
		schedules.add(wayPointId, schedule);
	}

	Schedule* getSchedule(int i) {
		return schedules.get(i);
	}
	Schedule* getSchedule(const string &id) {
		if (schedules.contains(id)) {
			return schedules.get(id);
		}
		return nullptr;
	}
	string& getId() {
		return id;
	}

	void printInformation(int current) {
		cout << "ID: " << schedules.get(current)->getId() << endl;;
		cout << "Next Waypoint: [" << "lat: " << schedules.get(current)->getX() << ", lon: " << 
			schedules.get(current)->getY() << ", alt: " << schedules.get(current)->getY() << "]" << endl;
	}
	int getScheduleSize() {
		return size;
	}
private:
	string id;
	Store<Schedule*> schedules;
	int size;
	
};
}
#endif