
#include <stdio.h>
#include <string>
#include <fstream>
#include <amqm/AMQManager.h>
#include <Utils.h>
#include "ImageReceiver.h"
#include <nlohmann/json.hpp>

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/imgproc/imgproc_c.h>

using namespace amqm;
using namespace cms;
using namespace std;
using namespace cv;

ImageReceiver::ImageReceiver() {
	amq.listen("imageDetected", std::bind(&ImageReceiver::updateImageDetected, this, _1), true);

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

    //Here pImageData is [unsigned char *] that points to a jpeg compressed image buffer;
    //     ImageDataSize is the size of compressed content in buffer;
    //     The image here is grayscale;

    vector<unsigned char> ImVec(img, img + size);
    cv:Mat ImMat;
    ImMat = imdecode(ImVec, 8);

    imshow("CLOSURE Image Receiver", ImMat);
    waitKey(3); // Wait for any keystroke in the window
}
