
#include <stdio.h>
#include <string>
#include <fstream>
#include <amqm/AMQManager.h>
#include <Utils.h>
#include "ImageReceiver.h"
#include <nlohmann/json.hpp>

#include <opencv2/opencv.hpp>
#include <heartbeat/HeartBeat.h>
#include <BlockingQueue.h>

using namespace amqm;
using namespace cms;
using namespace std;
using namespace cv;

BlockingQueue<json> messageQueue;
const string WINDOW_NAME = "CLOSURE Image Receiver";

ImageReceiver::ImageReceiver()
{
	amq.listen("receiveImageDetections", std::bind(&ImageReceiver::updateImageDetected, this, _1), true);

	json j = Utils::loadDefaultConfig();
	processConfigContent(j);
}

void ImageReceiver::processConfigContent(json j)
{
}

ImageReceiver::~ImageReceiver()
{
}

void ImageReceiver::updateImageDetected(const json &j)
{
    messageQueue.push(j);
}


void hexToBin(string hexData, char *image_buf, int image_buf_size)
{
    int buf_size = hexData.length();
    if (image_buf_size < buf_size / 2) {
        cout << "ERROR: buffer too small: " << buf_size << " v.s. " << image_buf_size << endl;
        buf_size = image_buf_size * 2;
    }

    int k = 0;
    for (int i = 0; i < buf_size; i += 2) {
        image_buf[k++] = std::stoul(hexData.substr(i, 2), nullptr, 16);
    }
}

void displayImage(const json &j)
{
    string name = j["A_name"].get<string>();
    int size = j["B_size"];
    string pad = j["C_pad"].get<string>();
    string meta = j["D_metadata"].get<string>();
    string imageData = j["E_imgData"].get<string>();

    cout << "Receiver rcvd " << name << " : " << size << " : " << meta << endl;

    char img[size];
    hexToBin(imageData, img, size);

    vector<unsigned char> imVec(img, img + size);
    cv:Mat mat;
    mat = imdecode(imVec, 8);

    cv::putText(mat, //target image
                "Name: " + name, //text
                cv::Point(10, mat.rows - 100), //top-left position
                cv::FONT_HERSHEY_DUPLEX,
                1.0,
                CV_RGB(235, 140, 52), //font color
                2);

    cv::putText(mat, //target image
                "Size: " + to_string(size), //text
                cv::Point(10, mat.rows - 50), //top-left position
                cv::FONT_HERSHEY_DUPLEX,
                1.0,
                CV_RGB(235, 140, 52), //font color
                2);

    cv::putText(mat, //target image
                "Meta: " + meta, //text
                cv::Point(10, mat.rows - 10), //top-left position
                cv::FONT_HERSHEY_DUPLEX,
                1.0,
                CV_RGB(235, 140, 52), //font color
                2);

    imshow(WINDOW_NAME, mat);
    waitKey(10); // Wait for any keystroke in the window
}

int displaySplash(string pathanme)
{
    std::string image_path = samples::findFile(pathanme);
    Mat img = imread(image_path, IMREAD_COLOR);
    if (img.empty()) {
        std::cout << "Could not read the image: " << image_path << std::endl;
        return 1;
    }
    Mat detectedFrame;
    img.convertTo(detectedFrame, CV_8U);

    imshow(WINDOW_NAME, detectedFrame);
    moveWindow(WINDOW_NAME, 900, 100);
    waitKey(1000); // Wait for any keystroke in the window

    return 0;
}

void ImageReceiver::run()
{
    displaySplash("config/images/splash.jpg");

    HeartBeat isrm_HB("ImageReceiver");
    isrm_HB.startup_Listener("ImageDetector");

    while (true) {
        json msg = messageQueue.pop();

        displayImage(msg);
    }
}

