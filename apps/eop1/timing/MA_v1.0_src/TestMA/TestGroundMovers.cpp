#include "TestGroundMovers.h"
#include <iostream>
#include <cmath>
#include <string>
#include <list>
#include <string>
#include <Ground_Movers.h>


const double GROUND_MOVERS_COR_TO_COR_MAX_ERROR = .01;

//void TestGroundMovers::testUpdateGroundVehiclePosition(void)
//{
//	Ground_Vehicle *gv = new Ground_Vehicle(1, 1, 0, 90);
//	uas::Location loc = gv->get_Curruent_Location();
//	CPPUNIT_ASSERT_EQUAL(1.0, loc.x);
//	CPPUNIT_ASSERT_EQUAL(1.0, loc.y);
//	Ground_Vehicle *gv2 = new Ground_Vehicle(32.715736, -117.161087, 500, 45);
//	uas::Location loc2 = gv2->get_Curruent_Location();
//	cout << "location x is " << loc2.y << endl;
//	Utils::sleep_for(5000);
//	cout << "location x is " << gv2->get_Curruent_Location().y << endl;
//	bool a = (loc2.x != 32.715736);
//	bool b = (loc2.y != -117.161087);
//	CPPUNIT_ASSERT(a);
//	CPPUNIT_ASSERT(b);
//	delete gv;
//	delete gv2;
//}

void TestGroundMovers::testGetCurruentLocation(void)
{
	Ground_Vehicle *gv = new Ground_Vehicle(1, 1, 0, 90);
	uas::Location loc = gv->get_Curruent_Location();
	CPPUNIT_ASSERT_EQUAL(1.0, loc.x);
	CPPUNIT_ASSERT_EQUAL(1.0, loc.y);
	delete gv;
}

void TestGroundMovers::testGetSpeed(void)
{
	Ground_Vehicle *gv = new Ground_Vehicle(1, 1, 3, 1);
	int i = gv->get_Speed();
	CPPUNIT_ASSERT_EQUAL(3, i);
	delete gv;
}

void TestGroundMovers::testGetBearing(void) 
{
	Ground_Vehicle *gv = new Ground_Vehicle(1, 1, 0, 3);
	double i = gv->get_Bearing();
	CPPUNIT_ASSERT_EQUAL(3.0, i);
	delete gv;
}

void TestGroundMovers::testCoordinateToCoordinate(void)
{
	Ground_Vehicle *gv = new Ground_Vehicle(0, 0, 0, 90);
	uas::Location loc = gv->CoordinateToCoordinate(0, 0, 90, 100);
	int expectedX = 0;
	int expectedY = .9;
	bool errorX = abs(expectedX - loc.x) < GROUND_MOVERS_COR_TO_COR_MAX_ERROR;
	bool errorY = abs(expectedY - loc.y) < GROUND_MOVERS_COR_TO_COR_MAX_ERROR;
	CPPUNIT_ASSERT(errorX);
	CPPUNIT_ASSERT(errorY);
	delete gv;
}