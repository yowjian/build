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

#ifndef TEST_SCHEDULE_H
#define TEST_SCHEDULE_H

class TestSchedule : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(TestSchedule);
	CPPUNIT_TEST(testSetData);
	CPPUNIT_TEST(testGetX);
	CPPUNIT_TEST(testGetY);
	CPPUNIT_TEST(testGetZ);
	CPPUNIT_TEST(testGetId);
	CPPUNIT_TEST(testGetPhase);
	CPPUNIT_TEST(testIsEgressPoint);
	CPPUNIT_TEST(testSetEgressPoint);
	CPPUNIT_TEST_SUITE_END();

public:

protected:
	void testSetData(void);
	void testGetX(void);
	void testGetY(void);
	void testGetZ(void);
	void testGetId(void);
	void testGetPhase(void);
	void testIsEgressPoint(void);
	void testSetEgressPoint(void);
private:

};

#endif
