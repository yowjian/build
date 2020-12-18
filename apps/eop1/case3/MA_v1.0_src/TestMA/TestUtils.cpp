#include "TestUtils.h"
#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/ui/text/TextTestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/BriefTestProgressListener.h>
#include <string>
#include <Utils.h>

void TestUtils::testConversions(void)
{
	CPPUNIT_ASSERT_EQUAL(Utils::deg2rad(180), M_PI);
	CPPUNIT_ASSERT_EQUAL(Utils::rad2deg(M_PI), 180.0);
}

void TestUtils::testWait(void) {
	auto begin = std::chrono::steady_clock::now();
	Utils::sleep_for(1000);
	auto end = std::chrono::steady_clock::now();
	auto def = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
	CPPUNIT_ASSERT(def >= 1000);
}

void TestUtils::testParse(void) {
	char plan[] = "{ \"missionPlan\": { \"missionPlanId\": \"id\", \"vehiclePlan\": { \"vehiclePlanId\": \"id\", \"numberOfWayPoints\": 3, \"wayPoints\": [ { \"wayPointId\": \"wp0\", \"x\": 0.1, \"y\": 0.1, \"z\": 0.1 }, { \"wayPointId\": \"wp1\", \"x\": 0.2, \"y\": 0.2, \"z\": 0.2 }, { \"wayPointId\": \"wp2\", \"x\": 0.3, \"y\": 0.3, \"z\": 0.3 }, { \"wayPointId\": \"wp3\", \"x\": 0.1, \"y\": 0.3, \"z\": 0.1 }, { \"wayPointId\": \"wp4\", \"x\": 0.5, \"y\": 0.5, \"z\": 0.5 } ] }, \"sensorPlan\": { \"sensorPlanId\": \"id\", \"vehiclePlanId\": \"id\", \"numberOfSensorWayPoints\": 1, \"actions\": [ { \"actionId\": \"ac1\", \"wayPointId\": \"wp1\", \"actionType\": \"find\" }, { \"actionId\": \"ac2\", \"wayPointId\": \"wp2\", \"actionType\": \"fix\" } ] } } }";
	MissionPlan* mPlan = Utils::parsePlan(json::parse(plan));
	string id = "id";
	CPPUNIT_ASSERT_EQUAL(mPlan->getScheduleSize(), 5);
	CPPUNIT_ASSERT_EQUAL(mPlan->getId(), id);
	delete mPlan;
}

void TestUtils::testDistance(void) {
	CPPUNIT_ASSERT_EQUAL(round(Utils::distanceEarth(1.0, 1.0, 2.0, 2.0)), 157.0);
}

void TestUtils::testBearing(void) {
	CPPUNIT_ASSERT_EQUAL(Utils::bearing(0, 0, 1, 1), 44.0);
}

void TestUtils::testIsNear(void) {
	CPPUNIT_ASSERT_EQUAL(Utils::isNear(0.5, 0.6), true);
}

void TestUtils::testGetNextLatLon(void) {
	double lat = 0;
	double lon = 0;
	Utils::getNextLatLon(lat, lon, 1, 1, 10);
	CPPUNIT_ASSERT_EQUAL(round(lat * 100), 6.0);
	CPPUNIT_ASSERT_EQUAL(round(lon * 100), 6.0);
}