#ifndef FOO_H
#define FOO_H

#include <iostream>
//#include <thread>

#include <amqm/AMQManager.h>
#include <nlohmann/json.hpp>
#include "ISRM_Find_Fix.h"

using namespace std;
using namespace std::placeholders;
using namespace amqm;
using json = nlohmann::json;

class FOO {

public:
    FOO() {
        amq.listen("recieveISRMDetections", std::bind(&FOO::recieveISRMDetections, this, _1), true);
        amq.listen("requestISRMDetections", std::bind(&FOO::handleDetectionsRequest, this, _1), true);
    }

private:
    AMQManager amq;

    void requestISRMDetections(const string &phase) {
        json js;
        js["phase"] = phase;
        amq.publish("requestISRMDetections", js, true);
    }

    void recieveISRMDetections(json j) {
        for (int i = 0; i < j.size(); i++) {
            int idn = j[i]["TGT_ISRM_ID"];
            string id = to_string(idn);
            double xD = j[i]["x"];
            double yD = j[i]["y"];
            double zD = 0;
            double speed = j[i]["speed"];
            double bearing = j[i]["bearing"];
            double conf = j[i]["confidence"];
            string classification = j[i]["classification"];
        }
    }

    void handleDetectionsRequest(json j) {
        ISRM_Data ISRM_Test_Data;
        string phase = j["phase"];
        json det;
        if (phase == "fix") {
            det = ISRM_Test_Data.send_Fix_Level_Detail();
        }
        else {
            det = ISRM_Test_Data.send_Find_Level_Detail();
        }
        amq.publish("recieveISRMDetections", det, true);
    }

};
#endif
