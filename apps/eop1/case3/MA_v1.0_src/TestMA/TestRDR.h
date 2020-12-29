#pragma once

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

#ifndef TEST_RDR_H
#define TEST_RDR_H

class TestRDR : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(TestRDR);
	CPPUNIT_TEST(testRequestRDRDetections);
	CPPUNIT_TEST_SUITE_END();

public:

protected:
	void testRequestRDRDetections(void);
private:

};

#endif