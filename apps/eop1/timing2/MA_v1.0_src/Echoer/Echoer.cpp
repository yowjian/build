
#include <stdio.h>
#include <string>
#include <fstream>

#include <amqm/AMQManager.h>
#include <Utils.h>
#include "Echoer.h"
#include <nlohmann/json.hpp>

#include <opencv2/opencv.hpp>
#include <heartbeat/HeartBeat.h>
#include <BlockingQueue.h>

using namespace amqm;
using namespace cms;
using namespace std;
using namespace cv;


Echoer::Echoer()
{
    amq.listen("component_heartbeats", std::bind(&Echoer::echo_component_heartbeats, this, _1), true);
    amq.listen("updateMissionPlan", std::bind(&Echoer::echo_updateMissionPlan, this, _1), true);
    amq.listen("recieveISRMDetections", std::bind(&Echoer::echo_component_heartbeats, this, _1), true);
    amq.listen("groundMovers", std::bind(&Echoer::echo_groundMovers, this, _1), true);
    amq.listen("requestISRMDetections", std::bind(&Echoer::echo_requestISRMDetections, this, _1), true);
    amq.listen("pnt", std::bind(&Echoer::echo_pnt, this, _1), true);
    amq.listen("requestEOIRDetections", std::bind(&Echoer::echo_requestEOIRDetections, this, _1), true);
    amq.listen("requestRDRDetections", std::bind(&Echoer::echo_requestRDRDetections, this, _1), true);
    amq.listen("recieveEOIRDetections", std::bind(&Echoer::echo_recieveEOIRDetections, this, _1), true);
    amq.listen("recieveRDRDetections", std::bind(&Echoer::echo_recieveRDRDetections, this, _1), true);

    json j = Utils::loadDefaultConfig();
    processConfigContent(j);
}

void Echoer::processConfigContent(json j)
{
}

Echoer::~Echoer()
{
}

void Echoer::echo_component_heartbeats(const json &j)
{
    amq.publish("component_heartbeats_remote", j, true);
}

void Echoer::echo_updateMissionPlan(const json &j)
{
    amq.publish("updateMissionPlan_remote", j, true);
}

void Echoer::echo_recieveISRMDetections(const json &j)
{
    amq.publish("recieveISRMDetections_remote", j, true);
}

void Echoer::echo_groundMovers(const json &j)
{
    amq.publish("groundMovers_remote", j, true);
}

void Echoer::echo_requestISRMDetections(const json &j)
{
    amq.publish("requestISRMDetections_remote", j, true);
}

void Echoer::echo_pnt(const json &j)
{
    amq.publish("pnt_remote", j, true);
}

void Echoer::echo_requestEOIRDetections(const json &j)
{
    amq.publish("requestEOIRDetections_remote", j, true);
}

void Echoer::echo_requestRDRDetections(const json &j)
{
    amq.publish("requestRDRDetections_remote", j, true);
}

void Echoer::echo_recieveEOIRDetections(const json &j)
{
    amq.publish("recieveEOIRDetections_remote", j, true);
}

void Echoer::echo_recieveRDRDetections(const json &j)
{
    amq.publish("recieveRDRDetections_remote", j, true);
}

void Echoer::run()
{
    HeartBeat isrm_HB("Echoer");
    isrm_HB.startup_Listener("Sender");

    json timeout;
    timeout["A_name"] = "timeout";

    Utils::sleep_forever();
//    while (true) {

//        json msg = messageQueue.pop(1, timeout);
//        string name = msg["A_name"].get<string>();
//
//        // imshow will not refresh the window after waitKey returns
//        // refresh it if no new message is received
//        if (!name.compare("timeout")) {
//            imshow(WINDOW_NAME, imageMat);
//            waitKey(10);
//        }
//        else {
////            displayImage(msg);
//        }
//    }
}

