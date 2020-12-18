#include "GAPS_openCV_Manager.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/imgproc/imgproc_c.h>
#include <math.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <exception>
// This is DOS API
//#include <conio.h>
#include <vector>
#include <unordered_map>

#include "Blob.h"

using namespace cv;
using namespace dnn;
using namespace std;

#define SHOW_STEPS


const cv::Scalar SCALAR_BLACK = cv::Scalar(0.0, 0.0, 0.0);
const cv::Scalar SCALAR_WHITE = cv::Scalar(255.0, 255.0, 255.0);
const cv::Scalar SCALAR_YELLOW = cv::Scalar(0.0, 255.0, 255.0);
const cv::Scalar SCALAR_GREEN = cv::Scalar(0.0, 200.0, 0.0);
const cv::Scalar SCALAR_RED = cv::Scalar(0.0, 0.0, 255.0);

struct blob_return
{
     vector<string> blob_Class;
     vector<double> blob_Confidence;
     std::vector<std::pair<double, double>> centerPositions;
};

void matchCurrentFrameBlobsToExistingBlobs(std::vector<Blob> &existingBlobs, std::vector<Blob> &currentFrameBlobs);
void addBlobToExistingBlobs(Blob &currentFrameBlob, std::vector<Blob> &existingBlobs, int &intIndex);
void addNewBlob(Blob &currentFrameBlob, std::vector<Blob> &existingBlobs);
double distanceBetweenPoints(cv::Point point1, cv::Point point2);
void classify(std::vector<Blob> &blobs, cv::Mat &frame, dnn::Net &net);
void sort_Blob_Returns(blob_return this_Blob);



float confThreshold = 0.5;
float nmsThreshold = 0.4;
int inpWidth = 64; 
int inpHeight = 64;
std::vector<std::string> classes;


std::map<std::string, GAPS_opencv_Return> image_contents;


void postprocess(cv::Mat& frame, const std::vector<cv::Mat>& out, int x, int y, int w, int h, blob_return &processed_Blob);

void drawPred(int classId, float conf, int left, int top, int right, int bottom, cv::Mat& frame);

vector<String> getOutputsNames(const Net& net);




std::map<std::string, GAPS_opencv_Return> run_GAPS_Video_Anaylsis()
{

     string classesFile = "coco.names";
     ifstream ifs(classesFile.c_str());
     string line;
     while (getline(ifs, line)) classes.push_back(line);

	 String modelConfiguration = "yolov3.cfg";
     String modelWeights = "yolov3.weights";

     Net net = readNetFromDarknet(modelConfiguration, modelWeights);
     net.setPreferableBackend(DNN_BACKEND_OPENCV);
     net.setPreferableTarget(DNN_TARGET_OPENCL);

     Mat frame, blob;



     cv::VideoCapture capVideo;

     cv::Mat imgFrame1;
     cv::Mat imgFrame2;

     std::vector<Blob> blobs;
     try
     {
          capVideo.open("walking.avi");
     }
     catch (exception& ex) {
        std::cout << ex.what() << std::endl;
     }
     if (!capVideo.isOpened()) {
          std::cout << "error reading video file" << std::endl << std::endl;
          return image_contents;
     }

     if (capVideo.get(cv::CAP_PROP_FRAME_COUNT) < 2) {
          std::cout << "error: video file must have at least two frames";
          return image_contents;
     }

     capVideo.read(imgFrame1);
     capVideo.read(imgFrame2);

     char chCheckForEscKey = 0;

     bool blnFirstFrame = true;

     int frameCount = 2;

     while (capVideo.isOpened() && chCheckForEscKey != 27) {

          std::vector<Blob> currentFrameBlobs;

          cv::Mat processFrame = imgFrame1.clone();
          cv::Mat compFrame = imgFrame2.clone();
          cv::Mat outputFrame = imgFrame2.clone();

          cv::Mat imgDifference;
          cv::Mat imgThresh;

          cv::cvtColor(processFrame, processFrame, cv::COLOR_BGR2GRAY);
          cv::cvtColor(compFrame, compFrame, cv::COLOR_BGR2GRAY);

          cv::GaussianBlur(processFrame, processFrame, cv::Size(5, 5), 0);
          cv::GaussianBlur(compFrame, compFrame, cv::Size(5, 5), 0);

          cv::absdiff(processFrame, compFrame, imgDifference);

          cv::threshold(imgDifference, imgThresh, 30, 255.0, cv::THRESH_BINARY);



          cv::Mat structuringElement3x3 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
          cv::Mat structuringElement5x5 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
          cv::Mat structuringElement7x7 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(7, 7));
          cv::Mat structuringElement9x9 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(9, 9));



          cv::dilate(imgThresh, imgThresh, structuringElement3x3);
          cv::dilate(imgThresh, imgThresh, structuringElement3x3);
          cv::erode(imgThresh, imgThresh, structuringElement3x3);

          cv::Mat imgThreshCopy = imgThresh.clone();

          std::vector<std::vector<cv::Point> > contours;

          cv::findContours(imgThreshCopy, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

          std::vector<std::vector<cv::Point> > convexHulls(contours.size());

          for (unsigned int i = 0; i < contours.size(); i++) {
               cv::convexHull(contours[i], convexHulls[i]);
          }

          for (auto &convexHull : convexHulls) {
               Blob possibleBlob(convexHull);

               if (possibleBlob.currentBoundingRect.area() > 100 &&
                    possibleBlob.dblCurrentAspectRatio >= 0.2 &&
                    possibleBlob.dblCurrentAspectRatio <= 1.25 &&
                    possibleBlob.currentBoundingRect.width > 20 &&
                    possibleBlob.currentBoundingRect.height > 20 &&
                    possibleBlob.dblCurrentDiagonalSize > 30.0 &&
                    (cv::contourArea(possibleBlob.currentContour) / (double)possibleBlob.currentBoundingRect.area()) > 0.40) {
                    currentFrameBlobs.push_back(possibleBlob);
               }
          }


          if (blnFirstFrame == true) {
               for (auto &currentFrameBlob : currentFrameBlobs) {
                    blobs.push_back(currentFrameBlob);
               }
          }
          else {
               matchCurrentFrameBlobsToExistingBlobs(blobs, currentFrameBlobs);
          }

          compFrame = imgFrame2.clone();

          currentFrameBlobs.clear();

          classify(blobs, outputFrame, net);

          imgFrame1 = imgFrame2.clone();

          if ((capVideo.get(cv::CAP_PROP_POS_FRAMES) + 1) < capVideo.get(cv::CAP_PROP_FRAME_COUNT)) {
               capVideo.read(imgFrame2);
          }
          else {
               std::cout << "end of video\n";
               return image_contents;
               break;
          }

          blnFirstFrame = false;
          frameCount++;
          chCheckForEscKey = cv::waitKey(1);
     }

     if (chCheckForEscKey != 27) {
          cv::waitKey(0);
     }


     return image_contents;
}
void matchCurrentFrameBlobsToExistingBlobs(std::vector<Blob> &existingBlobs, std::vector<Blob> &currentFrameBlobs) {

     for (auto &existingBlob : existingBlobs) {

          existingBlob.blnCurrentMatchFoundOrNewBlob = false;

          existingBlob.predictNextPosition();
     }

     for (auto &currentFrameBlob : currentFrameBlobs) {

          int intIndexOfLeastDistance = 0;
          double dblLeastDistance = 100000.0;

          for (unsigned int i = 0; i < existingBlobs.size(); i++) {
               if (existingBlobs[i].blnStillBeingTracked == true) {
                    double dblDistance = distanceBetweenPoints(currentFrameBlob.centerPositions.back(), existingBlobs[i].predictedNextPosition);

                    if (dblDistance < dblLeastDistance) {
                         dblLeastDistance = dblDistance;
                         intIndexOfLeastDistance = i;
                    }
               }
          }

          if (dblLeastDistance < currentFrameBlob.dblCurrentDiagonalSize * 1.15) {
               addBlobToExistingBlobs(currentFrameBlob, existingBlobs, intIndexOfLeastDistance);
          }
          else {
               addNewBlob(currentFrameBlob, existingBlobs);
          }

     }

     for (auto &existingBlob : existingBlobs) {

          if (existingBlob.blnCurrentMatchFoundOrNewBlob == false) {
               existingBlob.intNumOfConsecutiveFramesWithoutAMatch++;
          }

          if (existingBlob.intNumOfConsecutiveFramesWithoutAMatch >= 5) {
               existingBlob.blnStillBeingTracked = false;
          }

     }

}

void addBlobToExistingBlobs(Blob &currentFrameBlob, std::vector<Blob> &existingBlobs, int &intIndex) {

     existingBlobs[intIndex].currentContour = currentFrameBlob.currentContour;
     existingBlobs[intIndex].currentBoundingRect = currentFrameBlob.currentBoundingRect;

     existingBlobs[intIndex].centerPositions.push_back(currentFrameBlob.centerPositions.back());

     existingBlobs[intIndex].dblCurrentDiagonalSize = currentFrameBlob.dblCurrentDiagonalSize;
     existingBlobs[intIndex].dblCurrentAspectRatio = currentFrameBlob.dblCurrentAspectRatio;

     existingBlobs[intIndex].blnStillBeingTracked = true;
     existingBlobs[intIndex].blnCurrentMatchFoundOrNewBlob = true;
}

void addNewBlob(Blob &currentFrameBlob, std::vector<Blob> &existingBlobs) {

     currentFrameBlob.blnCurrentMatchFoundOrNewBlob = true;

     existingBlobs.push_back(currentFrameBlob);
}

double distanceBetweenPoints(cv::Point point1, cv::Point point2) {

     int intX = abs(point1.x - point2.x);
     int intY = abs(point1.y - point2.y);

     return(sqrt(pow(intX, 2) + pow(intY, 2)));
}


void classify(std::vector<Blob> &blobs, cv::Mat &frame, dnn::Net &net) {
     for (unsigned int i = 0; i < blobs.size(); i++) {
          if (blobs[i].blnStillBeingTracked == true) {
               cv::Rect roi;
               int x = blobs[i].currentBoundingRect.x;
               int y = blobs[i].currentBoundingRect.y;
               int width = blobs[i].currentBoundingRect.width;
               int height = blobs[i].currentBoundingRect.height;
               roi.x = blobs[i].currentBoundingRect.x;
               roi.y = blobs[i].currentBoundingRect.y;
               roi.width = blobs[i].currentBoundingRect.width;
               roi.height = blobs[i].currentBoundingRect.height;
               cv::Mat crop = frame(roi);

              
               try {
                    blobFromImage(crop, crop, 1 / 255.0, cvSize(inpWidth, inpHeight), Scalar(0, 0, 0), true, false);
               }
               catch (Exception &e) {
                    cout << "THE MESSAGE" + e.msg << endl;
               }

               net.setInput(crop);

               // Runs the forward pass to get output of the output layers
               vector<Mat> outs;
               try {
                    net.forward(outs, getOutputsNames(net));
               }
               catch (Exception &e) {
                    cout << "THE MESSAGE" + e.msg << endl;
               }

               blob_return temp_blob_return;
               postprocess(frame, outs, x, y, width, height, temp_blob_return);
               temp_blob_return.centerPositions.push_back(std::make_pair(x, y));
               sort_Blob_Returns(temp_blob_return);


               Mat detectedFrame;
               frame.convertTo(detectedFrame, CV_8U);
          }


     }


}


void postprocess(Mat& frame, const vector<Mat>& outs, int x, int y, int w, int h, blob_return& processed_Blob)
{
     vector<int> classIds;
     vector<float> confidences;
     vector<Rect> boxes;
     blob_return blob_Return;

     for (size_t i = 0; i < outs.size(); ++i)
     {

          float* data = (float*)outs[i].data;
          for (int j = 0; j < outs[i].rows; ++j, data += outs[i].cols)
          {
               Mat scores = outs[i].row(j).colRange(5, outs[i].cols);
               Point classIdPoint;
               double confidence;
               
               minMaxLoc(scores, 0, &confidence, 0, &classIdPoint);
               if (confidence > confThreshold)
               {
                    int centerX = (int)(data[0] * frame.cols);
                    int centerY = (int)(data[1] * frame.rows);
                    int width = (int)(data[2] * frame.cols);
                    int height = (int)(data[3] * frame.rows);
                    int left = centerX - width / 2;
                    int top = centerY - height / 2;

                    classIds.push_back(classIdPoint.x);
                    confidences.push_back((float)confidence);

                    boxes.push_back(Rect(left, top, width, height));
               }
          }
     }



     vector<int> indices;
     NMSBoxes(boxes, confidences, confThreshold, nmsThreshold, indices);
     for (size_t i = 0; i < indices.size(); ++i)
     {
          int idx = indices[i];
          Rect box = boxes[idx];
          drawPred(classIds[idx], confidences[idx], x, y,
               x + w, y + h, frame);
          processed_Blob.blob_Class.push_back(classes[classIds[idx]]);
          processed_Blob.blob_Confidence.push_back(confidences[idx]);


     }
}


void drawPred(int classId, float conf, int left, int top, int right, int bottom, Mat& frame)
{
     
     rectangle(frame, Point(left, top), Point(right, bottom), Scalar(255, 178, 50), 1.5);


     string label = format("%.2f", conf);
     if (!classes.empty())
     {
          CV_Assert(classId < (int)classes.size());
          label = classes[classId] + ":" + label;
     }


     int baseLine;
     Size labelSize = getTextSize(label, FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseLine);
     top = max(top, labelSize.height);
     rectangle(frame, Point(left, top - round(1.1*labelSize.height)), Point(left + round(1.1*labelSize.width), top + baseLine), Scalar(255, 255, 255), FILLED);
     putText(frame, label, Point(left, top), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0), 1);
}


vector<String> getOutputsNames(const Net& net)
{
     static vector<String> names;
     if (names.empty())
     {
         
          vector<int> outLayers = net.getUnconnectedOutLayers();


          vector<String> layersNames = net.getLayerNames();

        
          names.resize(outLayers.size());
          for (size_t i = 0; i < outLayers.size(); ++i)
               names[i] = layersNames[outLayers[i] - 1];
     }
     return names;
}

void sort_Blob_Returns(blob_return blob_returned)
{
     for (auto i = 0; i < blob_returned.blob_Class.size(); i++)
     {
          std::string temp_Class_Names = blob_returned.blob_Class[i];
          double temp_Confidence = blob_returned.blob_Confidence[i];
          std::vector<std::pair<double, double>> temp_centerPositions = blob_returned.centerPositions;


          if (image_contents.find(temp_Class_Names) != image_contents.end())
          {
               double compare_Confidence = image_contents.at(temp_Class_Names).image_Confidence;
               if (temp_Confidence > compare_Confidence)
               {
                    image_contents[temp_Class_Names].image_Confidence = temp_Confidence;
                    image_contents[temp_Class_Names].centerPositions = blob_returned.centerPositions;
               }
          }
          else 
          {
               GAPS_opencv_Return temp_gaps_return;
               temp_gaps_return.centerPositions = temp_centerPositions;
               temp_gaps_return.image_Confidence = temp_Confidence;
               image_contents.insert({ temp_Class_Names, temp_gaps_return });
          }

     }

}


void print_GAPS_openCV_Return(std::map<std::string, GAPS_opencv_Return> image_Values)
{
     for (auto it = image_Values.cbegin(); it != image_Values.cend(); ++it)
     {
          std::cout << it->first << " " << it->second.image_Confidence << "\n";
          std::cout << it->second.centerPositions[0].first << " , " << it->second.centerPositions[0].second << "\n";
     }
}

void update_To_Ground_Truth(std::map<std::string, GAPS_opencv_Return> &image_Values, double lat, double longitude)
{
     std::map<std::string, GAPS_opencv_Return>::iterator it = image_Values.begin();
     while (it != image_Values.end())
     {
          it->second.centerPositions[0].first = lat;
          it->second.centerPositions[0].second = longitude;
          it++;
     }
}


