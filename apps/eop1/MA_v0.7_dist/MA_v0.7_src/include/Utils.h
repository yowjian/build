#pragma once
#define earthRadiusKm 6371.0
#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath> 
#include <missions/MissionPlan.h>
#include <nlohmann/json.hpp>
#ifndef UTILS_H
#define UTILS_H
using namespace uas;
using json = nlohmann::json;

class Utils {
public :
	static MissionPlan* parsePlan(json const &input) {
		string mp = "missionPlan";
		string wp = "wayPoints";
		string vp = "vehiclePlan";
		int size = input[mp][vp][wp].size();
		MissionPlan *plan = new MissionPlan(input[mp]["missionPlanId"], size);
		for (int i = 0; i < size; i++) {
			plan->addSchedule(
				input[mp][vp][wp][i]["wayPointId"],
				input[mp][vp][wp][i]["x"],
				input[mp][vp][wp][i]["y"],
				input[mp][vp][wp][i]["z"]
			);
		}
		json sp = input[mp]["sensorPlan"];
		string actions = "actions";
		string wayPointId = "wayPointId";
		string actionType = "actionType";
		for (int i = 0; i < sp[actions].size(); i++) {
			string wpid = sp[actions][i][wayPointId];
			string aType = sp[actions][i][actionType];
			if (plan->getSchedule(wpid) != nullptr) {
				plan->getSchedule(wpid)->setPhase(aType);
			}
		}
		return plan;
	}

static double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d) {
	double lat1r, lon1r, lat2r, lon2r, u, v;
	lat1r = deg2rad(lat1d);
	lon1r = deg2rad(lon1d);
	lat2r = deg2rad(lat2d);
	lon2r = deg2rad(lon2d);
	u = sin((lat2r - lat1r) / 2);
	v = sin((lon2r - lon1r) / 2);
	return 2.0 * earthRadiusKm * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));
}
static double deg2rad(double deg) {
	return (deg * M_PI / 180);
}
static double bearing(double lat, double lon, double lat2, double lon2) {

	double teta1 = deg2rad(lat);
	double teta2 = deg2rad(lat2);
	double delta1 = deg2rad(lat2 - lat);
	double delta2 = deg2rad(lon2 - lon);

	//==================Heading Formula Calculation================//

	double y = sin(delta2) * cos(teta2);
	double x = cos(teta1)*sin(teta2) - sin(teta1)*cos(teta2)*cos(delta2);
	double brng = atan2(y, x);
	brng = rad2deg(brng);// radians to degrees
	brng = (((int)brng + 360) % 360);
	return brng;

}

//  This function converts radians to decimal degrees
static double rad2deg(double rad) {
	return (rad * 180 / M_PI);
}


static bool isNear(const double &distance, const double &within) {
	if (distance - within <= 0) {
		return true;
	}
	return false;
}

static void getNextLatLon(double &lat, double &lon, const double &waypointLat, 
const double &waypointLon, const double &s) {
	double d = (s);
	double tc = Utils::deg2rad(Utils::bearing(lat, lon,
		waypointLat,
		waypointLon
	));
	double dist = d / 6371;
	double brng = tc;
	double lat1 = deg2rad(lat);
	double lon1 = deg2rad(lon);

	double lat2 = asin(sin(lat1)*cos(dist) + cos(lat1)*sin(dist)*cos(brng));
	double a = atan2(sin(brng)*sin(dist)*cos(lat1), cos(dist) - sin(lat1)*sin(lat2));
	double lon2 = lon1 + a;

	lon2 = fmod((lon2 + 3 * M_PI) , (2 * M_PI) - M_PI);
	lat = rad2deg(lat2);
	lon = rad2deg(lon2);

}
};
#endif