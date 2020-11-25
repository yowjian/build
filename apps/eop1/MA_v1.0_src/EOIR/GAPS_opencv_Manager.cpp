#include "GAPS_openCV_Manager.h"
#include <math.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <exception>
#include <vector>
#include <unordered_map>

#include "Blob.h"


#define SHOW_STEPS


bool GAPS_openCV::init() {
	string classesFile = "coco.names";
	ifstream ifs(classesFile.c_str());
	string line;
	while (getline(ifs, line)) classes.push_back(line);

	String modelConfiguration = "yolov3.cfg";
	String modelWeights = "yolov3.weights";

	net = readNetFromDarknet(modelConfiguration, modelWeights);
	net.setPreferableBackend(DNN_BACKEND_OPENCV);
	net.setPreferableTarget(DNN_TARGET_OPENCL);



	try
	{
		capVideo.open("walking.avi");
	}
	catch (exception& ex) {
		std::cout << "ERROR" << std::endl;
	}
	if (!capVideo.isOpened()) {
		std::cout << "error reading video file" << std::endl << std::endl;
		return false;
	}

	if (capVideo.get(cv::CAP_PROP_FRAME_COUNT) < 2) {
		std::cout << "error: video file must have at least two frames";
		return false;
	}

	return true;
}

void  GAPS_openCV::run() {
	char chCheckForEscKey = 0;
	while (capVideo.isOpened() && chCheckForEscKey != 27) {
			capVideo.read(imgFrame1);
			if ((capVideo.get(cv::CAP_PROP_POS_FRAMES) + 1) >= capVideo.get(cv::CAP_PROP_FRAME_COUNT)) {
				std::cout << "end of video\n";
				break;
			}
			chCheckForEscKey = cv::waitKey(1);
			classifyEntireFrame(imgFrame1, net);
			
		
	}
	running = false;
}


 

void GAPS_openCV::matchCurrentFrameBlobsToExistingBlobs(std::vector<Blob> &existingBlobs, std::vector<Blob> &currentFrameBlobs) {

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

void  GAPS_openCV::addBlobToExistingBlobs(Blob &currentFrameBlob, std::vector<Blob> &existingBlobs, int &intIndex) {

     existingBlobs[intIndex].currentContour = currentFrameBlob.currentContour;
     existingBlobs[intIndex].currentBoundingRect = currentFrameBlob.currentBoundingRect;

     existingBlobs[intIndex].centerPositions.push_back(currentFrameBlob.centerPositions.back());

     existingBlobs[intIndex].dblCurrentDiagonalSize = currentFrameBlob.dblCurrentDiagonalSize;
     existingBlobs[intIndex].dblCurrentAspectRatio = currentFrameBlob.dblCurrentAspectRatio;

     existingBlobs[intIndex].blnStillBeingTracked = true;
     existingBlobs[intIndex].blnCurrentMatchFoundOrNewBlob = true;
}

void  GAPS_openCV::addNewBlob(Blob &currentFrameBlob, std::vector<Blob> &existingBlobs) {

     currentFrameBlob.blnCurrentMatchFoundOrNewBlob = true;

     existingBlobs.push_back(currentFrameBlob);
}

double  GAPS_openCV::distanceBetweenPoints(cv::Point point1, cv::Point point2) {

     int intX = abs(point1.x - point2.x);
     int intY = abs(point1.y - point2.y);

     return(sqrt(pow(intX, 2) + pow(intY, 2)));
}

void GAPS_openCV::classifyEntireFrame(const cv::Mat &frame, dnn::Net &net) {
	Mat blob;
	blobFromImage(frame, blob, 1 / 255.0, cvSize(inpWidth, inpHeight), Scalar(0, 0, 0), true, false);
	net.setInput(blob);
	vector<Mat> outs;
	net.forward(outs, getOutputsNames(net));
	postprocessframe(frame, outs);
	Mat detectedFrame;
	frame.convertTo(detectedFrame, CV_8U);
}

void GAPS_openCV::postprocessframe(const Mat& frame, const vector<Mat>& outs) {
	vector<int> classIds;
	vector<float> confidences;
	vector<Rect> boxes;

	for (size_t i = 0; i < outs.size(); ++i)
	{
		// Scan through all the bounding boxes output from the network and keep only the
		// ones with high confidence scores. Assign the box's class label as the class
		// with the highest score for the box.
		float* data = (float*)outs[i].data;
		for (int j = 0; j < outs[i].rows; ++j, data += outs[i].cols)
		{
			Mat scores = outs[i].row(j).colRange(5, outs[i].cols);
			Point classIdPoint;
			double confidence;
			// Get the value and location of the maximum score
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

	// Perform non maximum suppression to eliminate redundant overlapping boxes with
	// lower confidences
	vector<int> indices;
	cv::dnn::NMSBoxes(boxes, confidences, confThreshold, nmsThreshold, indices);
	for (size_t i = 0; i < indices.size(); ++i)
	{
		int idx = indices[i];
		Rect box = boxes[idx];
		string id = findObject(box.x + (box.width / 2), box.y + (box.height / 2));
		object det;
		det.centerPosition = std::pair<int, int>(box.x + (box.width / 2), box.y + (box.height / 2));
		det.confidence = confidences[idx];
		det.classification = classes[classIds[idx]];
		if (id.empty() && !classes.empty()) {
			det.id = classes[classIds[idx]] + std::to_string(++detectNum);
			image_contents[det.id] = det;
		}
		else {
				image_contents.erase(id);
				image_contents[id] = det;
		}
		drawPred(classIds[idx], confidences[idx], box.x, box.y,
			box.x + box.width, box.y + box.height, frame);
	}
}

void  GAPS_openCV::classify(const std::vector<Blob> &blobs, const cv::Mat &frame, dnn::Net &net) {
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
             


               Mat detectedFrame;
               frame.convertTo(detectedFrame, CV_8U);
          }


     }


}


void  GAPS_openCV::postprocess(const Mat& frame, const vector<Mat>& outs, int x, int y, int w, int h, blob_return& processed_Blob)
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
     cv::dnn::NMSBoxes(boxes, confidences, confThreshold, nmsThreshold, indices);
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


void  GAPS_openCV::drawPred(int classId, float conf, int left, int top, int right, int bottom, const Mat& frame)
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


vector<cv::String>  GAPS_openCV::getOutputsNames(const Net& n)
{
     vector<cv::String> names;
     if (names.empty())
     {
         
          vector<int> outLayers = net.getUnconnectedOutLayers();


          vector<cv::String> layersNames = net.getLayerNames();

          names.resize(outLayers.size());
          for (size_t i = 0; i < outLayers.size(); ++i)
	               names[i] = layersNames[outLayers[i] - 1];
     }
     return names;
}

std::map<std::string, object> GAPS_openCV::getMap() {
	return image_contents;
}

double GAPS_openCV::calculateDistance(int x1, int y1, int x2, int y2) {
	return sqrtf(powf(x2 - x1, 2) + powf(y2 - y1, 2) * 1.0);
}

string GAPS_openCV::findObject(int x, int y) {
	for (const auto &it : image_contents) {
		if (calculateDistance(x, y, it.second.centerPosition.first, it.second.centerPosition.second) <= 55) {
			return it.first;
		}
	}
	return "";
}

bool GAPS_openCV::isRunning() {
	return running;
}
