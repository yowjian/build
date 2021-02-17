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

#ifndef TEST_MISSION_PLAN_H
#define TEST_MISSION_PLAN_H

class TestMissionPlan : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(TestMissionPlan);
	CPPUNIT_TEST(testAddSchedule);
	CPPUNIT_TEST(testGetSchedule);
	CPPUNIT_TEST(testGetMap);
	CPPUNIT_TEST(testGetId);
	CPPUNIT_TEST(testGetScheduleSize);
	CPPUNIT_TEST_SUITE_END();

public:
	
protected:
	void testAddSchedule(void);
	void testGetSchedule(void);
	void testGetMap(void);
	void testGetId(void);
	void testGetScheduleSize(void);
private:

};

#endif
