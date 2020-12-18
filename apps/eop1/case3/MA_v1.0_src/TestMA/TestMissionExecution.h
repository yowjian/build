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

#ifndef TEST_MISSION_EXECUTION_H
#define TEST_MISSION_EXECUTION_H

class TestMissionExecution : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(TestMissionExecution);
	CPPUNIT_TEST(test);
	CPPUNIT_TEST_SUITE_END();

public:

protected:
	void test(void);
private:

};

#endif