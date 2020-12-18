#pragma once
#ifndef GROUND_MOVERS_H
#define GROUND_MOVERS_H
#include <chrono>
#include <random>
#include <iostream>
#include <math.h>
#include <string>
#include <thread>
#include <missions/CommonUAS.h>

#include <thread>
#include <iostream>
#include <nlohmann/json.hpp>
#include <missions/MissionPlan.h>
#include <nlohmann/json.hpp>
#include <fstream>
#include <stdio.h>
#include <string>
#include <sstream>
#include <amqm/AMQManager.h>
#include <Utils.h>

using namespace amqm;
/**
 * @brief speed of ground mover in kilometer per milisecond (rounded)
 * 
 */
const double KpMS = 0.0003;
/**
 * @brief speed of ground mover in kilometers per second
 * 
 */
const double KpS = 0.277777778;
/**
 * @todo Unused and unknown
 * 
 */
const double MpMS_CONST = 0.000277778;
/**
 * @brief Value of Pi as a global double
 * 
 */
static const double PI = 3.14159265358979323846;
/**
 * @brief earth diameter in meters
 * 
 */
static const double earthDiameterMeters = 6371.0 * 2 * 1000;
/**
 * @brief max total distance before change of bearing in kilometers
 * 
 */
static const double MAX_TOTAL_DISTANCE_KM = 40;
/**
 * @brief max total distance before change of bearing in meters
 * 
 */
static const double MAX_TOTAL_DISTANCE = MAX_TOTAL_DISTANCE_KM * 1000; //in meters

/**
* @brief – Class responsible for generating a new ground mover for detections and updating it every
* second
* 
*
* @author – Original Author - Christopher Seay
* @author – Last Edited By - Mases Krikorian
* @date – 8/31/2020
*
* @details – This process is not part of MA and does not need a heartbeat to start. This process will not 
* stop or terminate unless forced by the user. It generates a new moving object (near San Diego by default)
* for detection for EOIR and RDR, and updates its location every 1 second.
*
*/
class Ground_Vehicle
{
public:

	/**
	 * @brief Construct a new Ground_Vehicle object and generate a detection near San Diego
	 * moving speed randomly generated before 25-125 kpH and randomly generated bearing between
	 * 0 and 360 degrees and a random vehicle ID number between 1 and 500000 and spawning
	 * a new thread to update its location every second
	 * 
	 */
	Ground_Vehicle();
	
	/**
	 * @brief Construct a new Ground_Vehicle object and generate a detection near the given lat and lon
	 * moving speed randomly generated before 25-125 kpH and randomly generated bearing between
	 * 0 and 360 degrees and a random vehicle ID number between 1 and 500000 and spawning
	 * a new thread to update its location every second
	 * 
	 */
	Ground_Vehicle(double starting_Lat, double starting_Long);
	
	/**
	 * @brief Construct a new Ground_Vehicle object and generate a detection near San Diego
	 * moving based on the provided speed and bearing  random vehicle ID number between 1 and 
	 * 500000 and spawning a new thread to update its location every second
	 * 
	 */
	Ground_Vehicle(double starting_Lat, double starting_Long, double starting_Speed, double starting_Bearing);

	/**
	 * @brief update vehicle location based on the speed and bearing. If distance traveled
	 * is above the max allowed, vehicle will travel 90 degrees; effectively moving the vechile
	 * in a square-like shape, and sending the data through the "groundMovers" ActiveMQ channel
	 * 
	 * @param VOID
	 *
	 * @return VOID
	 */
	void Update_Ground_Vehicle_Position(void);

	/**
	 * @brief Get the Curruent Location object
	 * 
	 * @param VOID
	 *
	 * @return uas::Location with lat, lon, and alt members of the ground mover's location
	 */
	uas::Location get_Curruent_Location(void);
	/**
	 * @brief Get the Speed of ground mover in Kph
	 * 
	 * @param VOID
	 * 
	 * @return double speed of ground mover in Kph
	 */
	double get_Speed(void);
	/**
	 * @brief Get the Bearing of ground mover in degrees
	 * 
	 * @param VOID
	 *
	 * @return double bearing of ground mover in degrees
	 */
	double get_Bearing(void);

	
	/**
	 * @brief Get the next location of where the ground mover is meant to to be based on speed,
	 * bearing, and current location.
	 * 
	 * @param x - latitude of ground mover in degrees
	 * @param y  - longtitude of ground mover in degrees
	 * @param angle - bearing of ground mover in degrees
	 * @param meters  - distance to the distination waypoint (max allowed)
	 *
	 * @return uas::Location - location of where ground mover will be
	 */
	uas::Location CoordinateToCoordinate(double x, double y, double angle, double meters);
	/**
	 * @brief print where the ground mover is
	 * 
	 * @param VOID
	 * 
	 * @return VOID
	 */
	void print_Current_Location(void);
	/**
	 * @brief print where the ground mover is
	 * 
	 * @param VOID
	 * 
	 * @return VOID
	 */
	void print_Debug(void);

private:
	/**
     * @brief ActiveMQ Manager instance to listen and publish messages
     * 
    */
	AMQManager amq;
	/**
	 * @brief starting location of ground mover
	 * 
	 */
	uas::Location starting_Location;
	/**
	 * @brief current location of ground mover
	 * 
	 */
	uas::Location current_Location;
	/**
	 * @brief Unique ID of ground mover between 0 and 500000
	 * 
	 */
	int vehcile_ID;
	/**
	 * @brief speed of ground mover in KpH
	 * 
	 */
	double speed;
	/**
	 * @brief Speed / 3600
	 * 
	 */
	double MpMS;
	/**
	 * @brief bearing of ground mover in degrees
	 * 
	 */
	double bearing;
	/**
	 * @brief total distance traveled. This will be reset to 0 and ground mover 
	 * turned 90 degrees when max distance is reached
	 * 
	 */
	double distance_traveled = 0;
	/**
	 * @brief time elapsed since last calculation (1s) * MpMS
	 * 
	 */
	double leg_distance;
	/**
	 * @brief Unused variable
	 * 
	 */
	double correction_even = 0;
	/**
	 * @brief Unused variable
	 * 
	 */
	double correction_odd = 0;
	/**
	 * @brief time when the ground mover was initialized and started moving
	 * 
	 */
	std::chrono::system_clock::time_point starting_time;
	/**
	 * @brief time since the ground mover last moved
	 * 
	 */
	std::chrono::system_clock::time_point last_time;

	// TODO: future de-bugging, compare start to present calculation to last to now cal for sanity check
	//uas::Location last_Location; 
	//std::chrono::system_clock::time_point last_reference_time; 

};


#endif

