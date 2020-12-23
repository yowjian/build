#include "MPU.h"
#include <heartbeat/HeartBeat.h>
int main() {
	MPU mpu;
	HeartBeat mpu_HB("MPU");
	mpu_HB.startup_HeartBeats();
	mpu.run();
	Utils::sleep_forever();
	return 0;
}