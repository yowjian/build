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

#ifndef TEST_HEART_BEAT_H
#define TEST_HEART_BEAT_H

class TestHeartBeat : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(TestHeartBeat);
	CPPUNIT_TEST(testStartupHeartBeats);
	CPPUNIT_TEST(testStartupListener);
	CPPUNIT_TEST_SUITE_END();

public:

protected:
	void testStartupHeartBeats(void);
	void testStartupListener(void);
private:

};

#endif