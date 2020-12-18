#include "RDR.h"
#include <heartbeat/HeartBeat.h>
int main() {
	RDR rdr;
	HeartBeat rdr_HB("RDR");
	rdr_HB.startup_Listener();
	rdr.run();
	Utils::sleep_forever();
	return 0;
}