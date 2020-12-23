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

#ifndef TEST_ISRM_FIND_FIX_H
#define TEST_ISRM_FIND_FIX_H

class TestISRMFindFix : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(TestISRMFindFix);
	CPPUNIT_TEST(testSendFixLevelDetail);
	CPPUNIT_TEST(testSendFindLevelDetail);
	CPPUNIT_TEST_SUITE_END();

public:

protected:
	void testSendFixLevelDetail(void);
	void testSendFindLevelDetail(void);
private:

};

#endif