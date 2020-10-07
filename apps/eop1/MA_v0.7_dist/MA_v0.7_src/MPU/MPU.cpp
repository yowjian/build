#include "MPU.h"
#include <iostream>
#include <heartbeat/Heartbeat.h>
using namespace std;



int main() {
	HeartBeat mpu_HB = HeartBeat("MPU");
    mpu_HB.startup_HeartBeats();
	int num = 0;
	MPU mpu;
	mpu.loadPlan();
	while (num != -1) {
		cin >> num;
	}
	return 0;
}