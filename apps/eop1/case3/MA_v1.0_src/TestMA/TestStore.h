
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

#ifndef TEST_STORE_H
#define TEST_STORE_H

class TestStore : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(TestStore);
	CPPUNIT_TEST(testAdd);
	CPPUNIT_TEST(testClearAll);
	CPPUNIT_TEST(testRemove);
	CPPUNIT_TEST(testOverride);
	CPPUNIT_TEST(testGetIndex);
	CPPUNIT_TEST(testSize);
	CPPUNIT_TEST(testRemoveHead);
	CPPUNIT_TEST(testRemoveBack);
	CPPUNIT_TEST(testContains);
	CPPUNIT_TEST(testGetMap);
	CPPUNIT_TEST_SUITE_END();

public:
	
protected:
	void testAdd(void);
	void testRemove(void);
	void testOverride(void);
	void testGetIndex(void);
	void testClearAll(void);
	void testSize(void);
	void testRemoveHead(void);
	void testRemoveBack(void);
	void testContains(void);
	void testGetMap(void);
private:

};

#endif