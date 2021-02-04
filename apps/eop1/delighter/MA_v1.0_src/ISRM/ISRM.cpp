
#include <stdio.h>
#include <string>
#include <fstream>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <amqm/AMQManager.h>
#include <Utils.h>
#include "ISRM.h"

using namespace amqm;
using namespace cms;
using namespace std;
namespace fs = boost::filesystem;

ISRM::ISRM(int maxDetects) : planManager(5), detects(maxDetects) {
	amq.listen("updateMissionPlan", std::bind(&ISRM::updateMissionPlan, this, _1), true);
	amq.listen("requestISRMDetections", std::bind(&ISRM::handleDetectionsRequest, this, _1), true);
	amq.listen("recieveISRMDetectionsXD", std::bind(&ISRM::handleRecieveISRMDetectionsXD, this, _1), true);
	amq.listen("updateConfig", std::bind(&ISRM::handleUpdateConfig, this, _1), true);
	json j = Utils::loadDefaultConfig();
	processConfigContent(j);
	//collectDetects();
}

void ISRM::processConfigContent(json j) {
	detects.setSize(j["maxDetects"]);

	imageDir = j["imageDir"];
}

void ISRM::handleUpdateConfig(json j) {
	json k = Utils::loadConfig(j);
	processConfigContent(k);
}

ISRM::~ISRM() {
	planManager.clearAll();
	detects.clearAll();
}

bool selectIt()
{
    static bool inited = false;

    if (!inited) {
        srand( (unsigned)time(NULL) );
        inited = true;
    }

    /* skip rand() readings that would make n%6 non-uniformly distributed
          (assuming rand() itself is uniformly distributed from 0 to RAND_MAX) */
    int n = rand();
return true;
//    return (n & 0x1) == 0;
}

void readImage(string pathanem, char *img, int BUFFERSIZE)
{
    int size = BUFFERSIZE / 2 - 1;
    char buf[size];

    memset(buf, '\0', size);
    std::ifstream fin(pathanem, ios::in | ios::binary );
    fin.read(buf, size);
//    if (fin)
//      std::cout << "all characters read successfully.\n";
//    else
//      std::cout << "error: only " << fin.gcount() << " could be read\n";
    fin.close();

    char *p = img;
    for (int i = 0; i < size; i++)
        p += sprintf(p, "%02x", buf[i] & 0xff);
    printf("\n");
}

void padBuffer(char *buf, int size, char *prefix)
{
    memset(buf, '-', size);
    if (prefix != NULL) {
        sprintf(buf, prefix);
        buf[strlen(prefix)] = '-';
    }
    buf[size - 1] = '\0';
}

void ISRM::run() {
    fs::path dir(imageDir);

    if (!fs::exists(dir)) {
        cout << "directory " << " does not exist: " << imageDir << endl;
        exit(1);
    }

    const int IMAGE_HEX_SIZE = 40;
    char name[20];
    int size;
    char pad[240];
    padBuffer(pad, 240, NULL);

    char meta[64];
    padBuffer(meta, 64, "SENSITIVE");

    char img[IMAGE_HEX_SIZE]; // [9000];

    const string suffix = ".jpg";
    while (true) {
        for (const auto & entry : fs::directory_iterator(imageDir)) {
            std::cout << entry.path() << std::endl;
            string pathname = entry.path().string();
            if (pathname.length() >= suffix.length()) {
                if (0 == pathname.compare(pathname.length() - suffix.length(), suffix.length(), suffix)) {
                    if (!selectIt())
                        continue;

                    cout << "Select " << pathname << endl;
                    readImage(pathname, img, IMAGE_HEX_SIZE);

                    try {
                        size = fs::file_size(entry.path());
                        cout << "size of " << pathname << " is " << size << endl;

                        json j;
                        j["A_name"] = pathname;
                        j["B_size"] = size;
                        j["C_pad"] = pad;
                        j["D_meatdata"] = meta;
                        j["E_imgData"] = img;

                        cout << j.dump(2) << endl;

                        ISRM::amq.publish("updateMissionPlanXD", j, true);
                    }
                    catch (fs::filesystem_error &e) {
                        std::cout << e.what() << '\n';
                    }
                    break;
                }
            }
        }

        Utils::sleep_for(1000);
        cout << "ISRM wakes up." << endl;
    }
}

void ISRM::classify() {
}
void ISRM::print() {
	for (const auto& key_value : detects.getMap()) {
		cout << "id: " << key_value.first << endl;
		cout << "lat: " << key_value.second->getLat() << endl;
		cout << "lon: " << key_value.second->getLon() << endl;
		cout << "alt: " << key_value.second->getAlt() << endl;
		cout << "classification: " << key_value.second->getClassification() << endl;
		cout << "speed: " << key_value.second->getSpeed() << endl;
		cout << "bearing: " << key_value.second->getBearing() << endl;
		cout << "***********" << endl;
	}
}
void ISRM::collectDetects() {

	Detect *eoirDet1 = new Detect(0, 0, 0);
	eoirDet1->setClassification("tank");
	eoirDet1->setConfidence(0.7);


	Detect *rdrDet1 = new Detect(0.01, 0.01, 0.01);
	Detect *det2 = new Detect(1, 1, 1);
	rdrDet1->setConfidence(0.8);

	det2->setConfidence(0.9);
	det2->setClassification("bird");

	//detects.add("det1", eoirDet1);
	//detects.add("det2", rdrDet1);
	//detects.add("det3", det2);
	print();
	cout << "\n-------CORRELATING-------\n" << endl;
	correlate("det1", "det2");
	correlate("det2", "det3");
	correlate("det1", "det3");
	print();
}

void ISRM::appendMoreData() {
	if (detects.contains("det2")) {
		Detect *detect = detects.get("det2");
		detect->setSpeed(1.2);
		detect->setBearing(0.7);
	}
}
void ISRM::correlate(const string& id1, const string& id2) {
	if (detects.contains(id1) && detects.contains(id2)) {
		Detect *d1 = detects.get(id1);
		Detect *d2 = detects.get(id2);
		if ((std::ceil(d2->getLon() - 0.01 * 100.0) / 100.0) ==
			d1->getLon()) {

			d2->setClassification(d1->getClassification());
			detects.remove(id1);
		}
	}
}

void ISRM::handleDetectionsRequest(json j) {
	//return detections by adding properties to det here
	string phase = j["phase"];
//	json det;
//	amq.publish("requestRDRDetections", j, true);
//	amq.publish("requestEOIRDetections", j, true);
//	while (!rdrDataCollected || !eoirDataCollected) {
//		Utils::sleep_for(500);
//	}
//	eoirDataCollected = false;
//	rdrDataCollected = false;
//
//	det["detects"] = Utils::getDetectionsJson(detects);
//	amq.publish("recieveISRMDetections", det, true);

 	amq.publish("requestISRMDetectionsXD", j, true);
}

void ISRM::handleRecieveISRMDetectionsXD(json j) {
    amq.publish("recieveISRMDetections", j, true);
}

void ISRM::handleRecieveRDRDetections(json j) {
	rdrDataCollected = true;
	Utils::addDetections(detects, j["detects"]);
}

void ISRM::handleRecieveEOIRDetections(json j) {
	eoirDataCollected = true;
	Utils::addDetections(detects, j["detects"]);
}


void ISRM::updateMissionPlan(const json &j) {
	MissionPlan *plan = Utils::parsePlan(j);
	planManager.add(plan->getId(), plan);

        // updateMissionPlanXD is "reduced information set" for sharing
        json jc = j;
        json wp = jc["missionPlan"]["vehiclePlan"]["wayPoints"];
        for (int i=0; i < wp.size(); i++) wp[i]["z"] = 0.0;
        jc["missionPlan"]["vehiclePlan"]["wayPoints"] = wp;
       
        ISRM::amq.publish("updateMissionPlanXD", jc, true);
}
