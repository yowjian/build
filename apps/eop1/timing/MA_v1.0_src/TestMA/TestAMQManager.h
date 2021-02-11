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

#ifndef TEST_AMQ_MANAGER_H
#define TEST_AMQ_MANAGER_H

class TestAMQManager : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(TestAMQManager);
	CPPUNIT_TEST(testListen);
	CPPUNIT_TEST(testStopListening);
	CPPUNIT_TEST(testPublish);
	CPPUNIT_TEST_SUITE_END();

public:
	
protected:
	void testListen(void);
	void testStopListening(void);
	void testPublish(void);
private:

};

#endif