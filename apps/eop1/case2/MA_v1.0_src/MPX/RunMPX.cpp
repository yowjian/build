#include "MPX.h"
#include <heartbeat/HeartBeat.h>
int main() {
	MPX mpx;
	HeartBeat mpx_HB("MPX");
	mpx_HB.startup_Listener();
	Utils::sleep_forever();
	return 0;
}