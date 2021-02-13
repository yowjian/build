#include "ImageReceiver.h"
#include <heartbeat/HeartBeat.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <pthread.h>

using namespace cv;
using namespace std;

//static void*
//display_thread(void * param)
//{
//}

int main(int argc, char **argv)
{
//    pthread_t image_display_thread;
//
//    int rtn = pthread_create(&image_display_thread, NULL, &display_thread, NULL);
//    if (rtn != 0) {
//        exit(1);
//    }

//    xxx("config/images/test00.jpg");
	ImageReceiver isrm;
//	HeartBeat isrm_HB("ImageReceiver");
//	isrm_HB.startup_Listener("ImageDetector");
	isrm.run();
	Utils::sleep_forever();
	return 0;
}
