#include "ImageDetector.h"

#include <stdio.h>
#include <string>
#include <fstream>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <amqm/AMQManager.h>
#include <Utils.h>

#include <opencv2/opencv.hpp>

using namespace amqm;
using namespace cms;
using namespace std;
using namespace cv;
namespace fs = boost::filesystem;

ImageDetector::ImageDetector()
{
	amq.listen("receiveImageDetectionXDAck", std::bind(&ImageDetector::handleImageDetectedAck, this, _1), true);

	json j = Utils::loadDefaultConfig();
	processConfigContent(j);
}

void ImageDetector::processConfigContent(json j)
{
	imageDir = j["imageDir"];
}

ImageDetector::~ImageDetector() {
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

    return (n & 0x1) == 0;
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
    memset(buf, '-', size);
    if (prefix != NULL) {
        sprintf(buf, prefix);
        buf[strlen(prefix)] = '-';
    }
    buf[size - 1] = '\0';
}

int displayImage(string pathanme, int size, string meta)
{
    std::string image_path = samples::findFile(pathanme);
    Mat img = imread(image_path, IMREAD_COLOR);
    if (img.empty()) {
        std::cout << "Could not read the image: " << image_path << std::endl;
        return 1;
    }
    Mat detectedFrame;
    img.convertTo(detectedFrame, CV_8U);

    // cv::Mat img(512, 512, CV_8UC3, cv::Scalar(0));

    cv::putText(detectedFrame, //target image
                "Name: " + pathanme, //text
                cv::Point(10, img.rows - 100), //top-left position
                cv::FONT_HERSHEY_DUPLEX,
                1.0,
                CV_RGB(0, 255, 0), //font color
                2);

    cv::putText(detectedFrame, //target image
                "Size: " + to_string(size), //text
                cv::Point(10, img.rows - 50), //top-left position
                cv::FONT_HERSHEY_DUPLEX,
                1.0,
                CV_RGB(0, 255, 0), //font color
                2);

    cv::putText(detectedFrame, //target image
                "Meta: " + meta, //text
                cv::Point(10, img.rows - 10), //top-left position
                cv::FONT_HERSHEY_DUPLEX,
                1.0,
                CV_RGB(0, 255, 0), //font color
                2);

    imshow("CLOSURE Image Detector", detectedFrame);

    static int waittime = 3000;
    static int savedtime = waittime;

    int k = waitKey(waittime); // Wait for a keystroke in the window
    if (k == 'p') {
        savedtime = waittime;
        waittime = 0;
    }
    else if (k == '+')
        waittime += 1000;
    else if (k == '-') {
        waittime -= 1000;
        if (waittime <= 0)
            waittime = 1000;
    }
    else if (k != -1) {
        waittime = savedtime;
    }

    cout << "wait time = " << waittime << " ms" << endl;
    //    destroyWindow(pathanme); //destroy the created window

    return 0;
}

void ImageDetector::run()
{
    fs::path dir(imageDir);

    if (!fs::exists(dir)) {
        cout << "directory " << " does not exist: " << imageDir << endl;
        exit(1);
    }

    char pad[240];
    padBuffer(pad, 240, NULL);

    const string REDACT = "SENSITIVE";
    char meta[64];
    padBuffer(meta, 64, (char *)REDACT.c_str());
    string metaStr(meta);

    char pathname[20];

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
                j["A_name"] = pathname;
                j["B_size"] = size;
                j["C_pad"] = pad;
                j["D_meatdata"] = metaStr.replace(0, REDACT.length(), "XXXXXXXXX");
                j["E_imgData"] = string(hexImage);

                cout << "Detector sent " << pathname << " : " << size << " : " << meta << endl;

                ImageDetector::amq.publish("receiveImageDetectionXD", j, true);

                displayImage(pathname, size, meta);
            }
            catch (fs::filesystem_error &e) {
                std::cout << e.what() << '\n';
            }
        }
//        Utils::sleep_for(10000);
    }
}

void ImageDetector::handleImageDetectedAck(json j) {
    amq.publish("imageDetectedAck", j, true);
}

#if 0
void ImageDetector::run() {
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

                    displayImage(pathname);

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

                        ImageDetector::amq.publish("imageDetected", j, true);
                    }
                    catch (fs::filesystem_error &e) {
                        std::cout << e.what() << '\n';
                    }
                    break;
                }
            }
        }

        Utils::sleep_for(10000);
        cout << "Detector wakes up." << endl;
    }
}
#endif
