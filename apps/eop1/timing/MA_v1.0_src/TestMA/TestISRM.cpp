#include "TestISRM.h"
#include <iostream>
#include <string>
#include <list>
#include <string>
#include <ISRM.h>
#include <amqm/AMQManager.h>
#include <nlohmann/json.hpp>
using namespace amqm;
using json = nlohmann::json;


bool called = false;

void call(json j) {
	called = true;
}

void TestISRM::testHandleDetectionsRequest(void)
{
	ISRM isrm(10);
	AMQManager amq(false);
	amq.listen("requestRDRDetections", call, true);
	json j;
	j["phase"] = "find";
	isrm.handleDetectionsRequest(j);
	Utils::sleep_for(500);
	CPPUNIT_ASSERT_EQUAL(called, true);
	called = false;
	j.clear();
	amq.stopAll();


}