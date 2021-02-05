#include <heartbeat/HeartBeat.h>
#include "ImageDetector.h"

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

    imshow("CLOSURE", detectedFrame);
    waitKey(0); // Wait for any keystroke in the window

//    destroyWindow(pathanme); //destroy the created window

//    int k = waitKey(0); // Wait for a keystroke in the window
//    if (k == 's') {
//        imwrite("starry_night.png", img);
//    }

    return 0;
}

int main(int argc, char **argv) {
//
//    char buf[80];
//    while (true) {
//        for (int i = 0; i < 50; i++) {
//            sprintf(buf, "/home/tchen/images/test%02d.jpg", i);
//            xxx(buf);
//            Utils::sleep_for(1000);
//        }
//    }

	ImageDetector isrm;
	HeartBeat isrm_HB("ImageDetector");
	isrm_HB.startup_Listener("ImageReceiver");
	isrm.run();
	Utils::sleep_forever();
	return 0;
}
