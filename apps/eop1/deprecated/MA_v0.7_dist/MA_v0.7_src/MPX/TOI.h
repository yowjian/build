#pragma once
#ifndef TOI_H
#define TOI_H
#include <string>

using namespace std;

class TOI {
public:
	TOI(string id, double x, double y, double z, double speed,
		double bearing, double confidence, string classification) {
		this->id = id;
		this->x = x;
		this->y = y;
		this->z = z;
		this->speed = speed;
		this->bearing = bearing;
		this->confidence = confidence;
		this->classification = classification;
	}
	void setSpeedAndBearing(double speed, double bearing) {
		this->speed = speed;
		this->bearing = bearing;
	}
	string getId() {
		return id;
	}
	double getX() {
		return x;
	}

	double getY() {
		return y;
	}

	double getZ() {
		return z;
	}
	double getSpeed() {
		return speed;
	}
	double getBearing() {
		return bearing;
	}
	double getConfidence() {
		return confidence;
	}
	string getClassification() {
		return classification;
	}
	
private:
	string id;
	double x = -1;
	double y = -1;
	double z = -1;
	double speed = -1;
	double bearing = -1;
	double confidence = -1;
	string classification = "";
};	
#endif
