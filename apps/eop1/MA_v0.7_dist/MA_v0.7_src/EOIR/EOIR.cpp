#include <iostream>

#include <nlohmann/json.hpp>
#include "missions/MissionPlan.h"
#include <tsl/ordered_map.h>
#include "Store.h"
#include <iostream>
#include <heartbeat/HeartBeat.h>


#include "EOIR.h"
#include "GAPS_openCV_Manager.h"

using namespace std;
using namespace uas;


int main() {

	 HeartBeat eoir_HB = HeartBeat("EOIR");
     eoir_HB.startup_Listener();
     //std::map<std::string, GAPS_opencv_Return> test_Return;
     //test_Return = run_GAPS_Video_Anaylsis();
     //print_GAPS_openCV_Return(test_Return);
     //update_To_Ground_Truth(test_Return, 1.0, 2.0);
     //print_GAPS_openCV_Return(test_Return);

     unsigned char interrupt;
     EOIR *eoir = new EOIR();
     while(true){}
     return 0;
}