#include "ISRM.h"
#include <heartbeat/HeartBeat.h>
int main(int argc, char **argv) {
	ISRM isrm(100);
	HeartBeat isrm_HB("ISRM");
	isrm_HB.startup_Listener("ISRMshadow");
	isrm.run();
	Utils::sleep_forever();
	return 0;
}
