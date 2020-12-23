#include "TestDetect.h"
#include <iostream>
#include <string>
#include <list>
#include <string>
#include <missions/Detect.h>

using namespace uas;

void TestDetect::testDetect(void)
{
	Detect *det = new Detect(1, 2, 3);
	CPPUNIT_ASSERT_EQUAL(1.0, det->getLat());
	CPPUNIT_ASSERT_EQUAL(2.0, det->getLon());
	CPPUNIT_ASSERT_EQUAL(3.0, det->getAlt());
	delete det;
}

void TestDetect::testSetClassification(void)
{
	Detect *det = new Detect(1, 1, 1);
	det->setClassification("bird");
	int i = det->getClassification().compare("bird");
	CPPUNIT_ASSERT(i == 0);
	delete det;
}

void TestDetect::testSetSpeed(void)
{
	Detect *det = new Detect(1, 1, 1);
	det->setSpeed(2);
	CPPUNIT_ASSERT_EQUAL(2.0, det->getSpeed());
	delete det;
}

void TestDetect::testSetBearing(void)
{
	Detect *det = new Detect(1, 1, 1);
	det->setBearing(3);
	CPPUNIT_ASSERT_EQUAL(3.0, det->getBearing());
	delete det;
}

void TestDetect::testSetConfidence(void)
{
	Detect *det = new Detect(1, 1, 1);
	det->setConfidence(.68);
	CPPUNIT_ASSERT_EQUAL(.68, det->getConfidence());
	delete det;
}

void TestDetect::testSetLocation(void)
{
	Detect *det = new Detect(1, 1, 1);
	det->setLocation(3, 4, 5);
	CPPUNIT_ASSERT_EQUAL(3.0, det->getLat());
	CPPUNIT_ASSERT_EQUAL(4.0, det->getLon());
	CPPUNIT_ASSERT_EQUAL(5.0, det->getAlt());
	delete det;
}