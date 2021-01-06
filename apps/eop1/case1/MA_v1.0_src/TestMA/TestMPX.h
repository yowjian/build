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

#ifndef TEST_MPX_H
#define TEST_MPX_H

class TestMPX : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(TestMPX);
	CPPUNIT_TEST(testUpdateMissionPlan);
	CPPUNIT_TEST(testSetChanged);
	CPPUNIT_TEST(testCheckPlanStatus);
	CPPUNIT_TEST_SUITE_END();

public:

protected:
	void testUpdateMissionPlan(void);
	void testSetChanged(void);
	void testCheckPlanStatus(void);
private:

};

#endif