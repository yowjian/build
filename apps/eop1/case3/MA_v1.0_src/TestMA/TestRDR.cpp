#include "TestRDR.h"
#include <RDR.h>
#include <amqm/AMQManager.h>
#include <nlohmann/json.hpp>
using namespace amqm;
using json = nlohmann::json;

bool recieved = false;

void respRecieved(json j) {
	recieved = true;
}


void TestRDR::testRequestRDRDetections() {
	RDR rdr;
	AMQManager amq(false);
	amq.listen("recieveRDRDetections", respRecieved, true);
	json j;
	j["phase"] = "find";
	rdr.handleRequestRDRDetections(j);
	Utils::sleep_for(500);
	CPPUNIT_ASSERT_EQUAL(recieved, true);
	recieved = false;
	j.clear();

}
