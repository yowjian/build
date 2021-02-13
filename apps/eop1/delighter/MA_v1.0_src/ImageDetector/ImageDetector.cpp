#include "ImageDetector.h"

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

#define OVERLAY(text,pos)  cv::putText(imageMat,text,pos,ENCLAVE_FONT,FONT_SCALE,ENCLAVE_COLOR,FONT_THICKNESS)

static const string WINDOW_NAME = "CLOSURE Image Receiver";
static const cv::Scalar ENCLAVE_COLOR = CV_RGB(0, 255, 0);
static const cv::HersheyFonts  ENCLAVE_FONT = cv::FONT_HERSHEY_DUPLEX;
static const cv::Point NAME_POINT(10, 450);
static const cv::Point SIZE_POINT(10, 500);
static const cv::Point META_POINT(10, 550);
static const double FONT_SCALE = 1.0;
static const int FONT_THICKNESS = 2;

static cv::Mat imageMat;
static int waitTime = 3000;
static int savedTime = 0;

ImageDetector::ImageDetector()
{
	amq.listen("receiveImageDetectionXDAck", std::bind(&ImageDetector::handleImageDetectedAck, this, _1), true);

	json j = Utils::loadDefaultConfig();
	processConfigContent(j);
}

void ImageDetector::processConfigContent(json j)
{
	imageDir = Utils::getField(j, "imageDir");

	string waittimeStr = Utils::getField(j, "waitTime");
	if (!waittimeStr.empty())
	    waitTime = stoi(waittimeStr);
}

ImageDetector::~ImageDetector() {
}

void readImage(string pathanem, int image_size, char *buffer, int buffer_size)
{
    char img[image_size];

    std::ifstream fin(pathanem, ios::in | ios::binary);
    fin.read(img, image_size);
    if (!fin) {
        cout << "ERROR: image read, only " << fin.gcount() << " could be read\n";
    }
    fin.close();

    if (buffer_size < image_size * 2 + 1) {
        cout << "ERROR: buffer too small: " << (image_size * 2 + 1) << " v.s. " << buffer_size;
        image_size = (buffer_size - 1) / 2;
    }

    char *p = buffer;
    for (int i = 0; i < image_size; i++)
        p += sprintf(p, "%02x", img[i] & 0xff);

    buffer[image_size * 2] = '\0';
}

void padBuffer(char *buf, int size, const char *prefix)
{
    memset(buf, ' ', size);
    if (prefix != NULL) {
        sprintf(buf, prefix);
        buf[strlen(prefix)] = ' ';
    }
    buf[size - 1] = '\0';
}

void loadImage(string pathname, Mat &imageMat)
{
    std::string image_path = samples::findFile(pathname);
    Mat img = imread(image_path, IMREAD_COLOR);
    if (img.empty()) {
        std::cout << "Could not read the image: " << image_path << std::endl;
        return;
    }
    img.convertTo(imageMat, CV_8U);
}

void displaySplash(string pathname)
{
    loadImage(pathname, imageMat);

    imshow(WINDOW_NAME, imageMat);
    moveWindow(WINDOW_NAME, 900, 100);
    waitKey(1000); // Wait for any keystroke in the window
}

int displayImage(string pathname, int size, string meta, string objectName)
{
    loadImage(pathname, imageMat);

    OVERLAY("Name: " + objectName, NAME_POINT);
    OVERLAY("Size: " + to_string(size), SIZE_POINT);
    OVERLAY("Meta: " + meta, META_POINT);

    imshow(WINDOW_NAME, imageMat);

    int k = waitKey(waitTime); // Wait for a keystroke in the window

    if (k == 'p') {
        savedTime = waitTime;
        waitTime = 0;
    }
    else if (k == '+')
        waitTime += 1000;
    else if (k == '-') {
        waitTime -= 1000;
        if (waitTime <= 0)
            waitTime = 1000;
    }
    else if (k != -1) {
        waitTime = savedTime;
    }
    cout << "wait time = " << waitTime << " ms" << endl;

    return 0;
}

void ImageDetector::run()
{
    fs::path dir(imageDir);
    if (!fs::exists(dir)) {
        cout << "directory " << " does not exist: " << imageDir << endl;
        exit(1);
    }

    displaySplash(imageDir + "/splash-detector.jpg");

    HeartBeat isrm_HB("ImageDetector");
    isrm_HB.startup_Listener("ImageReceiver");

    char objname[20];

    char pad[240];
    padBuffer(pad, 240, NULL);

    const string REDACT = "REDONDO BEACH";
    char meta[64];
    padBuffer(meta, 64, (char *)REDACT.c_str());
    string metaStr(meta);

    char pathname[200];
    const string suffix = ".jpg";
    while (true) {
        for (int i = 0; i < 10; i++) {
            try {
                sprintf(pathname, "%s/test%02d.jpg", imageDir.c_str(), i);
                int size = fs::file_size(pathname);

                int hex_buf_size = size * 2 + 1;
                char hexImage[size * 2 + 1]; // [9000];
                readImage(pathname, size, hexImage, hex_buf_size);

                json j;
                string obj = "Object " + to_string(i);
                padBuffer(objname, 20, (char *)obj.c_str());
                j["A_name"] = objname;
                j["B_size"] = size;
                j["C_pad"] = pad;
                j["D_metadata"] = metaStr.replace(0, REDACT.length(), "XXXXXXXXX");
                j["E_imgData"] = string(hexImage);

                cout << "Detector sent " << objname << " : " << size << " : " << meta << endl;

                ImageDetector::amq.publish("receiveImageDetections", j, true);

                displayImage(pathname, size, meta, obj);
            }
            catch (fs::filesystem_error &e) {
                std::cout << e.what() << '\n';
            }
        }
    }
}

void ImageDetector::handleImageDetectedAck(json j)
{
    amq.publish("imageDetectedAck", j, true);
}
