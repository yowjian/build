#include "MPX.h"
#include "MissionExecution.h"
#include "MaintainProduct.h"
#include "missions/MissionPlan.h"
#include "Store.h"
#include <iostream>;
#include <heartbeat/HeartBeat.h>
using namespace std;
using namespace uas;
using json = nlohmann::json;

MaintainProduct *products = nullptr; 




class producer {
	//send C2 to ISRM
};

class consumer {
	//receive message from MPU and sensors  
};

//called from consumer 
void onMessage(const string& msg)
{
	//Process mission from MPU 
	MissionExecution::onReceivingMsnProgressMsg(msg);

	//Process sensor product   
	products->onReceivingSensorProducts(msg); 
}

int main() {
	HeartBeat mpx_HB = HeartBeat("MPX");
    mpx_HB.startup_Listener();
	MPX mpx;
	while(true){}
	return 0;
}



