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

#ifndef TEST_DETECT_H
#define TEST_DETECT_H

class TestDetect : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(TestDetect);
	CPPUNIT_TEST(testDetect);
	CPPUNIT_TEST(testSetClassification);
	CPPUNIT_TEST(testSetSpeed);
	CPPUNIT_TEST(testSetBearing);
	CPPUNIT_TEST(testSetConfidence);
	CPPUNIT_TEST(testSetLocation);
	CPPUNIT_TEST_SUITE_END();

public:

protected:
	void testDetect(void);
	void testSetClassification(void);
	void testSetSpeed(void);
	void testSetBearing(void);
	void testSetConfidence(void);
	void testSetLocation(void);
private:

};

#endif