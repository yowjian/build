#include "Sender.h"

#include <stdio.h>
#include <string>
#include <fstream>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <amqm/AMQManager.h>
#include <Utils.h>

#include <opencv2/opencv.hpp>
#include <heartbeat/HeartBeat.h>

using namespace amqm;
using namespace cms;
using namespace std;
using namespace cv;
namespace fs = boost::filesystem;

//static const string WINDOW_NAME = "CLOSURE Image Detector";

static bool synced = false;

static string messageDir = "../../../captured-messages";
static int instancesPerMessage = 10;
static int interval = 1000;

const static string MESSAGES[] = {
   "component_heartbeats",
   "updateMissionPlan",
   "pnt",
   "requestISRMDetections",
   "recieveISRMDetections",
   "requestEOIRDetections",
   "recieveEOIRDetections",
   "requestRDRDetections",
   "recieveRDRDetections",
   "groundMovers",
};

const static int NUM_MESSAGES = sizeof(MESSAGES) / sizeof(MESSAGES[0]);
static json messageJsons[NUM_MESSAGES];

Sender::Sender()
{
    amq.listen("component_heartbeats", std::bind(&Sender::echo_component_heartbeats, this, _1), true);
    amq.listen("updateMissionPlan", std::bind(&Sender::echo_updateMissionPlan, this, _1), true);
    amq.listen("recieveISRMDetections", std::bind(&Sender::echo_component_heartbeats, this, _1), true);
    amq.listen("groundMovers", std::bind(&Sender::echo_groundMovers, this, _1), true);
    amq.listen("requestISRMDetections", std::bind(&Sender::echo_requestISRMDetections, this, _1), true);
    amq.listen("pnt", std::bind(&Sender::echo_pnt, this, _1), true);
    amq.listen("requestEOIRDetections", std::bind(&Sender::echo_requestEOIRDetections, this, _1), true);
    amq.listen("requestRDRDetections", std::bind(&Sender::echo_requestRDRDetections, this, _1), true);
    amq.listen("recieveEOIRDetections", std::bind(&Sender::echo_recieveEOIRDetections, this, _1), true);
    amq.listen("recieveRDRDetections", std::bind(&Sender::echo_recieveRDRDetections, this, _1), true);

    amq.listen("component_heartbeats_remote", std::bind(&Sender::echo_component_heartbeats_remote, this, _1), true);
    amq.listen("updateMissionPlan_remote", std::bind(&Sender::echo_updateMissionPlan_remote, this, _1), true);
    amq.listen("recieveISRMDetections_remote", std::bind(&Sender::echo_component_heartbeats_remote, this, _1), true);
    amq.listen("groundMovers_remote", std::bind(&Sender::echo_groundMovers_remote, this, _1), true);
    amq.listen("requestISRMDetections_remote", std::bind(&Sender::echo_requestISRMDetections_remote, this, _1), true);
    amq.listen("pnt_remote", std::bind(&Sender::echo_pnt_remote, this, _1), true);
    amq.listen("requestEOIRDetections_remote", std::bind(&Sender::echo_requestEOIRDetections_remote, this, _1), true);
    amq.listen("requestRDRDetections_remote", std::bind(&Sender::echo_requestRDRDetections_remote, this, _1), true);
    amq.listen("recieveEOIRDetections_remote", std::bind(&Sender::echo_recieveEOIRDetections_remote, this, _1), true);
    amq.listen("recieveRDRDetections_remote", std::bind(&Sender::echo_recieveRDRDetections_remote, this, _1), true);

    json j = Utils::loadDefaultConfig();
    processConfigContent(j);
}

void Sender::processConfigContent(json j)
{
    messageDir = Utils::getField(j, "messageDir");
    instancesPerMessage = std::stoi(Utils::getField(j, "instancesPerMessage"), nullptr, 10);
    interval = std::stoi(Utils::getField(j, "interval"), nullptr, 10);
}

Sender::~Sender() {
}

static void proc_local(const string &topic, const json&j)
{
}

static void proc_remote(const string &topic, const json&j)
{
}

void Sender::echo_component_heartbeats(const json &j)
{
   if (synced)
      Utils::logElapsedTime(j, "component_heartbeats", false);
}

void Sender::echo_updateMissionPlan(const json &j)
{
   if (synced)
      Utils::logElapsedTime(j, "updateMissionPlan", false);
}

void Sender::echo_recieveISRMDetections(const json &j)
{
   if (synced)
      Utils::logElapsedTime(j, "recieveISRMDetections", false);
}

void Sender::echo_groundMovers(const json &j)
{
   if (synced)
      Utils::logElapsedTime(j, "groundMovers", false);
}

void Sender::echo_requestISRMDetections(const json &j)
{
   if (synced)
      Utils::logElapsedTime(j, "requestISRMDetections", false);
}

void Sender::echo_pnt(const json &j)
{
   if (synced)
      Utils::logElapsedTime(j, "pnt", false);
}

void Sender::echo_requestEOIRDetections(const json &j)
{
   if (synced)
      Utils::logElapsedTime(j, "requestEOIRDetections", false);
}

void Sender::echo_requestRDRDetections(const json &j)
{
   if (synced)
      Utils::logElapsedTime(j, "requestRDRDetections", false);
}

void Sender::echo_recieveEOIRDetections(const json &j)
{
   if (synced)
      Utils::logElapsedTime(j, "recieveEOIRDetections", false);
}

void Sender::echo_recieveRDRDetections(const json &j)
{
   if (synced)
      Utils::logElapsedTime(j, "recieveRDRDetections", false);
}

void Sender::echo_component_heartbeats_remote(const json &j)
{
   if (synced)
      Utils::logElapsedTime(j, "component_heartbeats", true);
}

void Sender::echo_updateMissionPlan_remote(const json &j)
{
   if (synced)
      Utils::logElapsedTime(j, "updateMissionPlan", true);
}

void Sender::echo_recieveISRMDetections_remote(const json &j)
{
   if (synced)
      Utils::logElapsedTime(j, "recieveISRMDetections", true);
}

void Sender::echo_groundMovers_remote(const json &j)
{
   if (synced)
      Utils::logElapsedTime(j, "groundMovers", true);
}

void Sender::echo_requestISRMDetections_remote(const json &j)
{
   if (synced)
      Utils::logElapsedTime(j, "requestISRMDetections", true);
}

void Sender::echo_pnt_remote(const json &j)
{
   if (synced)
      Utils::logElapsedTime(j, "pnt", true);
}

void Sender::echo_requestEOIRDetections_remote(const json &j)
{
   if (synced)
      Utils::logElapsedTime(j, "requestEOIRDetections", true);
}

void Sender::echo_requestRDRDetections_remote(const json &j)
{
   if (synced)
      Utils::logElapsedTime(j, "requestRDRDetections", true);
}

void Sender::echo_recieveEOIRDetections_remote(const json &j)
{
   if (synced)
      Utils::logElapsedTime(j, "recieveEOIRDetections", true);
}

void Sender::echo_recieveRDRDetections_remote(const json &j)
{
   if (synced)
      Utils::logElapsedTime(j, "recieveRDRDetections", true);
}

void readMessages()
{                                                                                           
   for (int i = 0; i < NUM_MESSAGES; i++) {
      std::ifstream msgStream(messageDir + "/" + MESSAGES[i] + ".json");
      if (msgStream.fail()) {                                                              
         cout << "ERROR: failed to read " << MESSAGES[i] << endl;
         continue;
      }
      msgStream >> messageJsons[i];                                                             
      msgStream.close();

      // cout << MESSAGES[i] << "\n" << messageJsons[i].dump(2) << endl << endl;
   }
}                                                                                           
  
void Sender::run()
{
    HeartBeat isrm_HB("Sender");
    isrm_HB.startup_Listener("Echoer");

    // wait for all pre-sync HB to be received.
    Utils::sleep_for(1000);
    synced = true;

    readMessages();
    
    for (int j = 0; j < instancesPerMessage; j++) {
        for (int i = 0; i < NUM_MESSAGES; i++) {
            try {
                cout << (j + 1) << "[" << instancesPerMessage << "] / "
                     << (i + 1) << "[" << NUM_MESSAGES << "] " << MESSAGES[i] << endl;
                amq.publish(MESSAGES[i], messageJsons[i], true);
            }
            catch (fs::filesystem_error &e) {
                std::cout << e.what() << '\n';
            }
            Utils::sleep_for(interval);
        }
    }

    cout << "Done\n";
    Utils::logAvgTime(instancesPerMessage);
}

