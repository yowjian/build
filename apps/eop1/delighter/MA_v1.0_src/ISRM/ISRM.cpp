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

ISRM::ISRM() {
	amq.listen("recieveISRMDetectionsXD", std::bind(&ISRM::handleRecieveISRMDetectionsXD, this, _1), true);

	json j = Utils::loadDefaultConfig();
	processConfigContent(j);
}

void ISRM::processConfigContent(json j) {
	imageDir = j["imageDir"];
}

ISRM::~ISRM() {
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

void ISRM::handleRecieveISRMDetectionsXD(json j) {
    amq.publish("recieveISRMDetections", j, true);
}


