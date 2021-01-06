#pragma once
#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/ui/text/TextTestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/BriefTestProgressListener.h>

#ifndef TEST_GROUND_MOVERS_H
#define TEST_GROUND_MOVERS_H

class TestGroundMovers : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(TestGroundMovers);
	//CPPUNIT_TEST(testUpdateGroundVehiclePosition);
	CPPUNIT_TEST(testGetCurruentLocation);
	CPPUNIT_TEST(testGetSpeed);
	CPPUNIT_TEST(testGetBearing);
	CPPUNIT_TEST(testCoordinateToCoordinate);
	CPPUNIT_TEST_SUITE_END();

public:

protected:
	//void testUpdateGroundVehiclePosition(void);
	void testGetCurruentLocation(void);
	void testGetSpeed(void);
	void testGetBearing(void);
	void testCoordinateToCoordinate(void);
private:

};

#endif#
