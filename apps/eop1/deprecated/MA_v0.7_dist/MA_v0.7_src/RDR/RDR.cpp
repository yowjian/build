#include <iostream>
#include <heartbeat/HeartBeat.h>
#include "RDR.h"
int main() {
	HeartBeat rdr_HB = HeartBeat("RDR");
    rdr_HB.startup_Listener();
	RDR rdr;
	while (true) {}
	return 0;
}