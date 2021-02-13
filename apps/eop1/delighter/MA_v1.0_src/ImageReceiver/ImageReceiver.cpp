
#include <stdio.h>
#include <string>
#include <fstream>
#include <amqm/AMQManager.h>
#include <Utils.h>
#include "ImageReceiver.h"
#include <nlohmann/json.hpp>

#include <opencv2/opencv.hpp>

using namespace amqm;
using namespace cms;
using namespace std;
using namespace cv;

ImageReceiver::ImageReceiver() {
	amq.listen("receiveImageDetections", std::bind(&ImageReceiver::updateImageDetected, this, _1), true);

	json j = Utils::loadDefaultConfig();
	processConfigContent(j);
}

void ImageReceiver::processConfigContent(json j) {
}

ImageReceiver::~ImageReceiver() {
}

void ImageReceiver::run() {

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

void ImageReceiver::updateImageDetected(const json &j)
{
    string name = j["A_name"].get<string>();
    int size = j["B_size"];
    string pad = j["C_pad"].get<string>();
    string meta = j["D_meatdata"].get<string>();
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

    imshow("CLOSURE Image Receiver", mat);

    static bool moved = false;
    if (!moved) {
        moveWindow("CLOSURE Image Receiver", 900, 0);
        moved = true;
    }
    waitKey(10); // Wait for any keystroke in the window
}
