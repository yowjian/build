
#include <stdio.h>
#include <string>
#include "Ground_Movers.h"
#include <amqm/AMQManager.h>
#include <heartbeat/HeartBeat.h>
#include "ISRM.h"

using namespace activemq;
using namespace activemq::core;
using namespace activemq::transport;
using namespace amqm;
using namespace cms;
using namespace std;

int main(int argc, char **argv) {
	HeartBeat isrm_HB = HeartBeat("ISRM");
    isrm_HB.startup_Listener();
	Ground_Vehicle *gr = new Ground_Vehicle();
	Ground_Vehicle *gr2 = new Ground_Vehicle();

	ISRM isrm(100);

	while(true){}
	return 0;
}