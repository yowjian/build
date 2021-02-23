#pragma once
#define earthRadiusKm 6371.0
#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath> 
#include <fstream>
#include <missions/MissionPlan.h>
#include <nlohmann/json.hpp>
#include <thread>
#include <chrono>
#include <missions/Detect.h>

#ifndef UTILS_H
#define UTILS_H
using namespace uas;
using json = nlohmann::json;
using namespace std;
using namespace std::chrono;

// start all components on the same day!
static long TIME_NOWMS = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
static long TIME_BASE = TIME_NOWMS - (TIME_NOWMS % (24 * 60 * 60 * 1000));

static map<string, map<string, double>> totalmap;  // message to local /xd to total elaspsed time


/**
* @brief – Class responsible for providing useful functions that can be used by all systems.
*
* @author – Original Author - Mases Krikorian
* @author – Last Edited By - Frederick Santiago
* @date – 9/15/2020
*
* @details – Utils provides various methods that can be used by all systems. Functions that include
* putting a thread to sleep, various unit conversions and other useful mathematical calculations, handling mission plan, 
* and any other logic that can be useful for more than one system. All functions are provided statically.
*/
class Utils {
public :
	/**
	 * @brief put the calling thread to sleep forever
	 * 
	 * @param VOID
	 *
	 * @return VOID
	 */
	static void sleep_forever() {
		std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::hours((std::numeric_limits<int>::max)()));
	}


	/**
	 * @brief puts the calling thread to sleep for a given time in milliseconds
	 * 
	 * @param milliseconds - duration of sleep in milliseconds
	 *
	 * @return VOID
	 */
	static void sleep_for(long milliseconds) {
		std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
	}

	/**
	 * @brief given a storage of detections, add a new detection to the storage
	 * 
	 * @param detects - a store of detects 
	 * @param j - new detection in json format
	 * 
	 * @return VOID
	 */
	static void addDetections(Store<Detect *> &detects, json j) {
		Detect * detect;
		for (int i = 0; i < j.size(); i++) {
			string id = j[i]["TGT_ISRM_ID"];
			if (detects.contains(id)) {
				detects.get(id)->setLocation(j[i]["lat"], j[i]["lon"], j[i]["alt"]);
				if (j[i]["bearing"] >= 0) {
					detects.get(id)->setBearing(j[i]["bearing"]);
				}
				if (! j[i]["classification"].empty()) {
					detects.get(id)->setClassification(j[i]["classification"]);
				}
				
				if (j[i]["speed"] >= 0) {
					detects.get(id)->setSpeed(j[i]["speed"]);
				}
				if (j[i]["confidence"] >= 0) {
					detects.get(id)->setConfidence(j[i]["confidence"]);
				}
			}
			else {
				detect = new Detect(j[i]["lat"], j[i]["lon"], j[i]["alt"], id, j[i]["speed"], j[i]["bearing"]);
				detects.add(id, detect);
			}
		}
	}
	/**
	 * @brief Get the Detections Json object from a store of detects
	 * 
	 * @param detects storage of detects using an ordered map
	 *
	 * @return json - an array of json object containing TGT_ISRM_ID, lat, lon, alt, bearing, speed
	 * confidence, classification
	 */
	static json getDetectionsJson(Store<Detect *> &detects) {
		json body;
		json out = json::array();
		for (auto key_value : detects.getMap()) {
			body["TGT_ISRM_ID"] = key_value.second->getId();
			body["lat"] = key_value.second->getLat();
			body["lon"] = key_value.second->getLon();
			body["alt"] = key_value.second->getAlt();
			body["bearing"] = key_value.second->getBearing();
			body["speed"] = key_value.second->getSpeed();
			body["confidence"] = key_value.second->getConfidence();
			body["classification"] = key_value.second->getClassification();
			out.push_back(body);
			body.clear();
		}
		return out;
	}
	/**
	 * @brief given a json input following a mission plan format, this function will extract the required values
	 * for mission plan, vehicle plan, and sensor plan
	 * 
	 * @param input - json object with data vehicle plan (waypoints) and sensor plan (actions at waypoints)
	 *
	 * @return MissionPlan* - a pointer to a new MissionPlan instance that can be added to a store
	 */
	static MissionPlan* parsePlan(json const &input) {
		string mp = "missionPlan";
		string wp = "wayPoints";
		string vp = "vehiclePlan";
		int size = input[mp][vp][wp].size();
		MissionPlan *plan = new MissionPlan(input[mp]["missionPlanId"], size);
		for (int i = 0; i < size; i++) {
			plan->addSchedule
			(
				input[mp][vp][wp][i]["wayPointId"],
				input[mp][vp][wp][i]["x"],
				input[mp][vp][wp][i]["y"],
				input[mp][vp][wp][i]["z"]
			);
		}
		plan->getSchedule(size - 1)->setEgressPoint(true);
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
/**
 * @brief given 2 sets of latitude and longtitude in degrees, calculate the distance between them in kilometers
 * 
 * @param lat1d - latitdue in degrees of position 1 
 * @param lon1d - longtitude in degrees of position 1
 * @param lat2d - latitude in degrees of position 2
 * @param lon2d - longtitude in degrees of position 2
 *
 * @return double - distance betwen the 2 points
 */
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
/**
 * @brief convert degrees to radians
 * 
 * @param deg - value in degrees
 *
 * @return double - convert value of degrees to radians
 */
static double deg2rad(double deg) {
	return (deg * M_PI / 180);
}

/**
 * @brief given 2 sets of latitude and longtitude in degrees, calculate the bearing between them in degrees
 * 
 * @param lat - latitdue in degrees of position 1 
 * @param lon - longtitude in degrees of position 1 
 * @param lat2 - latitdue in degrees of position 2
 * @param lon2 - longtitude in degrees of position 2
 *
 * @return double - bearing betweem the two points in degrees
 */
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

/**
 * @brief convert radians to degrees
 * 
 * @param rad - value to be converted to radians
 *
 * @return double - value converted to radians
 */
static double rad2deg(double rad) {
	return (rad * 180 / M_PI);
}

/**
 * @brief given a distance, calculate if the distance is within a certain constant
 * 
 * @param distance - current distance to another point
 * @param within - considered near is distance is within this value
 *
 * @return true if distance is within the value
 *
 */
static bool isNear(const double &distance, const double &within) {
	if (distance - within <= 0) {
		return true;
	}
	return false;
}
/**
 * @brief Override the referrence value of the latitude and longtitude based on current location and speed of unit
 * 
 * @param lat - current latitude in degrees of unit
 * @param lon - current longtitude in degrees of unit
 * @param waypointLat - destination latitude in degrees
 * @param waypointLon - desttination longtitude in degrees
 * @param s - speed of unit in km / s
 */
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

	lat = rad2deg(lat2);
	lon = rad2deg(lon2);

}
/**
 * @brief will look for the default json locally
 *
 * @param VOID
 *
 * @return default json
 *
 */
static json loadDefaultConfig() {
	std::ifstream k("config/defaultConfig.json");
	json j;
	k >> j;
	k.close();
	return j;
}
/**
 * @brief will look for the local json that corresponds to a configPlan
 *
 * @param configPlan - the configuration plan that is requested to be loaded
 *
 * @return the loaded json
 *
 */
static json loadConfig(json configPlan) {
	string config = "config/";
	string jsonFile = ".json";
	string configFile = configPlan["configPlan"];
	string str = config + configFile + jsonFile;
	std::ifstream k(str);
	json j;
	if (!k) return j;
	k >> j;
	k.close();
	return j;
}

static string getField(json js, string field)
{
    if (js.find(field) == js.end()) {
        cout << "No such field " + field << endl;
        return "";
    }
    string val;
    try {
        val = js[field];
    }
    catch (nlohmann::detail::type_error &e) {
        val = to_string(js[field]);
    }

    return val;
}

static long getTimestamp() {
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() - TIME_BASE;
}

static long getElapsedTime(json j) {
    auto ms_since_epoch = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() - TIME_BASE;
    return ms_since_epoch - j["timestamp"].get<long>();
}

static void logElapsedTime(json j, string msg, bool fromRemote) {
    static ofstream ofs("timings.csv");

    double elapsedTime = Utils::getElapsedTime(j);    // round trip
    string loc = (fromRemote ? "xd" : "local");

    ofs // << getTimestamp() << ","
        << msg << ", "
        << loc << ", "
        << elapsedTime
        << "\n"
        << std::flush;

//    static map<string, map<string, long>> count;

    map<string, map<string, double>>::iterator it = totalmap.find(loc);
    map<string, double> *tmap;
    if (it == totalmap.end()) {
        totalmap.insert(make_pair(loc, map<string, double>()));
        it = totalmap.find(loc);
    }
    tmap = &(it->second);

    double curr = 0;
    map<string, double>::iterator it2 = tmap->find(msg);
    if (it2 != tmap->end()) {
        curr = it2->second;
    }
    (*tmap)[msg] = curr + elapsedTime;
}

static void logAvgTime(int count)
{
    static ofstream ofs("average.csv");

    map<string, map<string, double>>::iterator itr;
    map<string, double>::iterator ptr;

    for (itr = totalmap.begin(); itr != totalmap.end(); itr++) {
        for (ptr = itr->second.begin(); ptr != itr->second.end(); ptr++) {
            ofs << ptr->first << ", "
                << itr->first << ", "
                <<  (ptr->second / count) / 2   // round trip
                << endl;
        }
    }
}
};
#endif
