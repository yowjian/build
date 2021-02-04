#include "ImageReceiver.h"
#include <heartbeat/HeartBeat.h>
int main(int argc, char **argv) {
	ImageReceiver isrm;
	HeartBeat isrm_HB("ImageReceiver");
	isrm_HB.startup_Listener("ImageDetector");
	isrm.run();
	Utils::sleep_forever();
	return 0;
}
