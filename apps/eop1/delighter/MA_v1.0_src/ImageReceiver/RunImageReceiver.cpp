#include "ImageReceiver.h"
#include <heartbeat/HeartBeat.h>
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int xxx(string pathanme)
{
    std::string image_path = samples::findFile(pathanme);
    Mat img = imread(image_path, IMREAD_COLOR);
    if (img.empty()) {
        std::cout << "Could not read the image: " << image_path << std::endl;
        return 1;
    }
    Mat detectedFrame;
    img.convertTo(detectedFrame, CV_8U);

    imshow("CLOSURE Image Receiver", detectedFrame);
    waitKey(1000); // Wait for any keystroke in the window

    return 0;
}

int main(int argc, char **argv) {
    xxx("config/images/test00.jpg");
	ImageReceiver isrm;
	HeartBeat isrm_HB("ImageReceiver");
	isrm_HB.startup_Listener("ImageDetector");
	isrm.run();
	Utils::sleep_forever();
	return 0;
}
