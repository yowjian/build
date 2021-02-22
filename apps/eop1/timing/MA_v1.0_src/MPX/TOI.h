#pragma once
#ifndef TOI_H
#define TOI_H
#include <string>

using namespace std;
/**
* @brief – Class responsible for structure of a Target of Interest
*
* @author – Original Author -Mases Krikorian
* @author – Last Edited By - Mases Krikorian
* @date – 8/28/2020
*
* @details – stores information about a TOI recieved from ISRM including
* id, x, y, z, speed, bearing, confidence, and classification
* 
*/
class TOI {
public:
	/**
	 * @brief Construct a new TOI object
	 * 
	 * @param id - unique identifier of detection / TOI
	 * @param x - corresponding to lat in degrees
	 * @param y - corresponding to lon in degrees
	 * @param z  - corresponding to alt in degrees
	 * @param speed - speed of detection / TOI in KpH
	 * @param bearing - bearing of detection / TOI in degrees
	 * @param confidence - confidence of detection / TOI between 0-1
	 * @param classification - classifcation of detection / TOI (eg. car)
	 */
	TOI(string id, double x, double y, double z, double speed,
		double bearing, double confidence, string classification);
	/**
	 * @brief Set the Speed And Bearing of TOI after FIX phase
	 * 
	 * @param speed - speed in KpH
	 * @param bearing - bearing in degrees
	 *
	 * @return VOID
	 */
	void setSpeedAndBearing(double speed, double bearing);
	/**
	 * @brief Get the Id object
	 * 
	 * @param VOID
	 *
	 * @return string object id
	 */
	string getId();
	/**
	 * @brief get X/Lat value in degrees
	 * 
	 * @param VOID
	 *
	 * @return double X/Lat value in degrees
	 */
	double getX();
	/**
	 * @brief get Y/Lon Value in degrees
	 * 
	 * @param VOID
	 *
	 * @return double get Y/Lon value in degrees
	 */
	double getY();
	/**
	 * @brief get Z/Alt value in degrees
	 * 
	 * @param VOID
	 *
	 * @return double get Z/Alt value in degrees
	 */
	double getZ();
	/**
	 * @brief Get the Speed in KpH
	 * 
	 * @param VOID
	 *
	 * @return double get the speed in KpH
	 */
	double getSpeed();
	/**
	 * @brief Get the Bearing in degrees
	 * 
	 * @param VOID
	 *
	 * @return double get bearing in degrees
	 */
	double getBearing();
	/**
	 * @brief Get the Confidence of TOI between 0 and 1
	 * 
	 * @param VOID
	 *
	 * @return double  Confidence of TOI between 0 and 1
	 */
	double getConfidence();
	/**
	 * @brief Get the Classification of TOI. Check EOIR/coco.names for list of 
	 * possible classifications
	 * 
	 * @param VOID
	 *
	 * @return string Classification of TOI. Check EOIR/coco.names for list of 
	 * possible classifications
	 */
	string getClassification();
	
private:
	/**
	 * @brief unqiue identifier for TOI
	 * 
	 */
	string id;
	/**
	 * @brief X/Lat of TOI. Initially -1
	 * 
	 */
	double x = -1;
	/**
	 * @brief Y/Lon of TOI. Initially -1
	 * 
	 */
	double y = -1;
	/**
	 * @brief Z/Alt of TOI. Initially -1
	 * 
	 */
	double z = -1;
	/**
	 * @brief Speed in KpH of TOI. Initially -1
	 * 
	 */
	double speed = -1;
	/**
	 * @brief bearing in degrees of TOI. Initially -1
	 * 
	 */
	double bearing = -1;
	/**
	 * @brief confidence of TOI between 0-1. Initially -1
	 * 
	 */
	double confidence = -1;
	/**
	 * @brief classification from a list available in EOIR/coco.names
	 * Initially empty ("")
	 * 
	 */
	string classification = "";
};	
#endif
