#include "TOI.h"

TOI::TOI(string id, double x, double y, double z, double speed,
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
void TOI::setSpeedAndBearing(double speed, double bearing) {
	this->speed = speed;
	this->bearing = bearing;
}
string TOI::getId() {
	return id;
}
double TOI::getX() {
	return x;
}

double TOI::getY() {
	return y;
}

double TOI::getZ() {
	return z;
}
double TOI::getSpeed() {
	return speed;
}
double TOI::getBearing() {
	return bearing;
}
double TOI::getConfidence() {
	return confidence;
}
string TOI::getClassification() {
	return classification;
}