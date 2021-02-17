
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
#ifndef TEST_UTILS_H
#define TEST_UTILS_H

class TestUtils : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(TestUtils);
	CPPUNIT_TEST(testConversions);
	CPPUNIT_TEST(testWait);
	CPPUNIT_TEST(testParse);
	CPPUNIT_TEST(testDistance);
	CPPUNIT_TEST(testBearing);
	CPPUNIT_TEST(testIsNear);
	CPPUNIT_TEST(testGetNextLatLon);
	CPPUNIT_TEST_SUITE_END();

public:

protected:
	void testConversions(void);
	void testWait(void);
	void testParse(void);
	void testDistance(void);
	void testBearing(void);
	void testIsNear(void);
	void testGetNextLatLon(void);
private:

};

#endif