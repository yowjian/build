#include <heartbeat/HeartBeat.h>
#include "ImageDetector.h"
int main(int argc, char **argv) {
	ImageDetector isrm;
	HeartBeat isrm_HB("ImageDetector");
	isrm_HB.startup_Listener("ImageReceiver");
	isrm.run();
	Utils::sleep_forever();
	return 0;
}
