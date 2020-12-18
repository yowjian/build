#pragma once
#ifndef DETECT_H
#define DETECT_H
#include <missions/CommonUAS.h>
class Detect {
public:
	int num = 1;
	Detect(double x, double y, double z){
		location.x = x;
		location.y = y;
		location.z = z;
	}
	string getClassification() {
		return classification;
	}
	void setClassification(string c) {
		classification = c;
	}
	void setSpeed(double s) {
		speed = s;
	}
	void setBearing(double b) {
		bearing = b;
	}

	void setConfidence(double c) {
		confidence = c;
	}

	void setLocation(double x, double y, double z) {
		location.x = x;
		location.y = y;
		location.z = z;
	}
	double getLat() {
		return location.x;
	}
	double getLon() {
		return location.y;
	}
	double getAlt() {
		return location.z;
	}
	double getBearing() {
		return bearing;
	}
	double getSpeed() {
		return speed;
	}
	double getConfidence() {
		return confidence;
	}
private:
	string classification;
	uas::Location location;
	double speed = -1; //km
	double bearing = -1; //radians
	double confidence = -1;

};
#endif