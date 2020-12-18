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

#ifndef TEST_ISRM_H
#define TEST_ISRM_H

class TestISRM : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(TestISRM);
	CPPUNIT_TEST(testHandleDetectionsRequest);
	CPPUNIT_TEST_SUITE_END();

public:

protected:
	void testHandleDetectionsRequest(void);
private:

};

#endif