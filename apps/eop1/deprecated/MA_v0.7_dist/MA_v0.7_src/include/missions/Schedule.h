#pragma once
#ifndef SCHEDULE_H
#define SCHEDULE_H
#include <string>
#include <missions/CommonUAS.h>
using namespace std;
using namespace uas;
enum Phase {FIND, FIX, TRACK, TARGET, NONE};
namespace uas {
struct Waypoint {
	Waypoint() {

	}
	Waypoint(double x, double y, double z) {
		loc.x = x;
		loc.y = y;
		loc.z = z;
	}
	Location loc;

};
class Schedule {
public:
	Schedule(string pid, double x, double y, double z) {
		id = pid;
		waypoint.loc.x = x;
		waypoint.loc.y = y;
		waypoint.loc.z = z;
	}
	Schedule() {}
	void setData(string pid, double x, double y, double z) {
		id = pid;
		waypoint.loc.x = x;
		waypoint.loc.y = y;
		waypoint.loc.z = z;
	}
	double getX() {
		return (waypoint.loc.x);
	}
	double getY() {
		return (waypoint.loc.y);
	}
	double getZ() {
		return (waypoint.loc.z);
	}
	string& getId() {
		return id;
	}
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
private:
	string id;
	Waypoint waypoint;
	Phase p;

};
}
#endif
