#pragma once
#ifndef ISRMDETECT_H
#define ISRMDETECT_H
#include <missions/CommonUAS.h>
typedef enum Classification { THREAT, FRIENDLY, NEUTRAL, UNKNOWN } Classification;
class ISRMDetect {
public:
	int num = 1;
	ISRMDetect(double la, double ln, double al){
		location.x = la;
		location.y = ln;
		location.z = al;
	}
	Classification getClassification() {
		return cls;
	}
	void setClassification(Classification c) {
		cls = c;
	}
	void setSpeed(double s) {
		speed = s;
	}
	void setBearing(double b) {
		bearing = b;
	}

	void setLocation(double la, double ln, double al) {
		location.x = la;
		location.y = ln;
		location.z = al;
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
private:
	Classification cls = UNKNOWN;
	uas::Location location;
	double speed = -1; //km
	double bearing = -1; //radians

};
#endif