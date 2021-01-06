#pragma once
#include <string>
#ifndef DETECT_H
#define DETECT_H
#include <missions/CommonUAS.h>
using namespace std;
namespace uas {
	/**
	* @brief – Class responsible for structure of a detection
	*
	* @author – Original Author - Mases Krikorian
	* @author – Last Edited By - Mases Krikorian
	* @date – 9/2/2020
	*
	* @details – a common detection structure for all sensors and managers which includes information 
	* such as location, speed, bearing, classification, and confidence
	*/
	class Detect {
	public:
		/**
		 * @brief Construct a new Detect object with a known location
		 * 
		 * @param x - x/lat (in degrees) value of object
		 * @param y - y/lon (in degrees) value of object
		 * @param z - z/alt (in degrees)  value of object
		 */
		Detect(double x, double y, double z) {
			location.x = x;
			location.y = y;
			location.z = z;
		}
		/**
		 * @brief Construct a new Detect object with a known location and an id
		 * 
		 * @param x - x/lat (in degrees) value of object
		 * @param y - y/lon (in degrees)  value of object
		 * @param z - z/alt (in degrees)  value of object
		 * @param id - id of the object detected
		 */
		Detect(double x, double y, double z, string id) {
			location.x = x;
			location.y = y;
			location.z = z;
			this->id = id;
		}/**
		 * @brief Construct a new Detect object with known location, id, speed, and bearing
		 * 
		 * @param x - x/lat (in degrees) value of object
		 * @param y - y/lon (in degrees) value of object
		 * @param z - z/alt (in degrees) value of object
		 * @param id - id of the object detected
		 * @param speed - speed in km/s
		 * @param bearing - bearing in degrees
		 */
		Detect(double x, double y, double z, string id, double speed, double bearing) {
			location.x = x;
			location.y = y;
			location.z = z;
			this->id = id;
			this->speed = speed;
			this->bearing = bearing;
		}
		/**
		 * @brief Get the Classification object
		 * 
		 * @param VOID
		 *
		 * @return string classification of detected object
		 */
		string getClassification() {
			return classification;
		}/**
		 * @brief Set the Classification object
		 * 
		 * @param c - string classification
		 *
		 * @return VOID
		 */
		void setClassification(string c) {
			classification = c;
		}
		/**
		 * @brief Get the Id object
		 * 
		 * @param VOID
		 *
		 * @return string object id
		 */
		string getId() {
			return id;
		}
		/**
		 * @brief Set the Id object
		 * 
		 * @param id - string identification of object
		 *
		 * @return VOID
		 */
		void setId(const string& id) {
			this->id = id;
		}
		/**
		 * @brief Set the Speed object
		 * 
		 * @param s - speed of object in km/s
		 */
		void setSpeed(double s) {
			speed = s;
		}
		/**
		 * @brief Set the Bearing object
		 * 
		 * @param b - bearing of object in degrees
		 * 
		 * @return VOID
		 */
		void setBearing(double b) {
			bearing = b;
		}
		/**
		 * @brief Set the Confidence object
		 * 
		 * @param c - condience of object between 0-1
		 *
		 * @return VOID
		 */
		void setConfidence(double c) {
			confidence = c;
		}
		/**
		 * @brief Set the Location object
		 * 
		 * @param x - x/lat (in degrees) value of object
		 * @param y - y/lon (in degrees) value of object
		 * @param z - z/alt (in degrees) value of object
		 *
		 * @return VOID
		 */
		void setLocation(double x, double y, double z) {
			location.x = x;
			location.y = y;
			location.z = z;
		}
		/**
		 * @brief Get the Lat object
		 * 
		 * @param VOID 
		 *
		 * @return double - lat/x value of object
		 */
		double getLat() {
			return location.x;
		}
		/**
		 * @brief Get the Lon object
		 *  
		 * @param VOID 
		 *
		 * @return double - lon/y value of object
		 */
		double getLon() {
			return location.y;
		}
		/**
		 * @brief Get the Alt object
		 *  
		 * @param VOID 
		 *
		 * @return double - alt/z value of object
		 */
		double getAlt() {
			return location.z;
		}
		/**
		 * @brief Get the Bearing object
		 *  
		 * @param VOID 
		 *
		 * @return double - bearing of object in degrees
		 */
		double getBearing() {
			return bearing;
		}
		/**
		 * @brief Get the Speed object
		 *  
		 * @param VOID 
		 *
		 * @return double 
		 */
		double getSpeed() {
			return speed;
		}
		/**
		 * @brief Get the Confidence object
		 *  
		 * @param VOID 
		 *
		 * @return double - confidence of object classification between 0-1
		 */
		double getConfidence() {
			return confidence;
		}
	private:
		/**
		 * @brief Classification of object detected
		 * 
		 */
		string classification;
		/**
		 * @brief Location of object detected
		 * 
		 */
		uas::Location location;
		/**
		 * @brief Speed of object detect in km/s, -1 by default 
		 * 
		 */
		double speed = -1;
		/**
		 * @brief Bearing of object detected in degrees, -1 by default
		 * 
		 */
		double bearing = -1; 
		/**
		 * @brief Confidence of object detected ranging between 0 and 1, -1 by default
		 * 
		 */
		double confidence = -1;
		/**
		 * @brief Id of object detected
		 * 
		 */
		string id;

	};
}
#endif