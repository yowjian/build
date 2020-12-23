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

#ifndef TEST_MESSAGE_HANDLER_H
#define TEST_MESSAGE_HANDLER_H

class TestMessageHandler : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(TestMessageHandler);
	CPPUNIT_TEST(testClose);
	CPPUNIT_TEST(testRunConsumer);
	CPPUNIT_TEST(testOnMessage);
	CPPUNIT_TEST(testRunConsumer);
	CPPUNIT_TEST_SUITE_END();

public:

protected:
	void testClose(void);
	void testRunConsumer(void);
	void testOnMessage(void);
	void testCleanUp(void);
private:

};

#endif