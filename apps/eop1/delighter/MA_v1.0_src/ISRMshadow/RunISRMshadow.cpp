#include "ISRMshadow.h"
#include <heartbeat/HeartBeat.h>
int main(int argc, char **argv) {
	ISRMShadow isrm(100);
	HeartBeat isrm_HB("ISRMshadow");
	isrm_HB.startup_Listener("ISRM");
	isrm.run();
	Utils::sleep_forever();
	return 0;
}
