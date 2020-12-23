#include "EOIR.h"
#include <heartbeat/HeartBeat.h>
#include "GAPS_openCV_Manager.h"
#include <unordered_map>

int main() {
	EOIR eoir;
	HeartBeat eoir_HB("EOIR");
	eoir_HB.startup_Listener();

	eoir.run();
	Utils::sleep_forever();
	return 0;
}