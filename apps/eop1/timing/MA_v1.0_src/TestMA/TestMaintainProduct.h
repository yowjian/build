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

#ifndef TEST_MAINTAIN_PRODUCT_H
#define TEST_MAINTAIN_PRODUCT_H

class TestMaintainProduct : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(TestMaintainProduct);
	CPPUNIT_TEST(testOnReceivingSensorProducts);
	CPPUNIT_TEST(testMaintainStore);
	CPPUNIT_TEST(testGetDetects);
	CPPUNIT_TEST(testGetFIX);
	CPPUNIT_TEST(testGetTRACK);
	CPPUNIT_TEST(testGetTARGET);
	CPPUNIT_TEST_SUITE_END();

public:

protected:
	void testOnReceivingSensorProducts(void);
	void testMaintainStore(void);
	void testGetDetects(void);
	void testGetFIX(void);
	void testGetTRACK(void);
	void testGetTARGET(void);
private:

};

#endif