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

#ifndef TEST_MPU_H
#define TEST_MPU_H

class TestMPU : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(TestMPU);
	CPPUNIT_TEST(testLoadPlan);
	CPPUNIT_TEST_SUITE_END();

public:

protected:
	void testLoadPlan(void);
private:

};

#endif