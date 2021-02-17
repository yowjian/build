#pragma once
#ifndef GAPS_OPENCV_MANAGER_H
#define GAPS_OPENCV_MANAGER_H
#include <map>
#include <vector>
#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/imgproc/imgproc_c.h>
#include "Blob.h"

using namespace cv;
using namespace dnn;
using namespace std;
/**
 * @brief Deprecated return for detecting moving objects
 * \deprecated
 */
struct GAPS_opencv_Return
{
	 ///confidence of detection
     double image_Confidence;
	 /// location of detection
     std::vector<std::pair<double, double>> centerPositions;
};

/**
 * @brief Deprecated moving blob information
 * \deprecated
 */
struct blob_return
{
	///classification of moving object
	vector<string> blob_Class;
	/// confidence of detection
	vector<double> blob_Confidence;
	/// location of detections
	std::vector<std::pair<double, double>> centerPositions;
};

/**
 * @brief Object detected by OpenCV's image recognition and deep neural network
 * 
 */
struct object {
	/// unique id of object
	string id;
	/// confidence of detection
	double confidence;
	//// classification of detection
	string classification;
	/// updated location of detection
	std::pair<int, int> centerPosition;
};

class GAPS_openCV {
private:
	/**
	 * @brief Color black represented with cv::Scalar RGB
	 * 
	 */
	const cv::Scalar SCALAR_BLACK = cv::Scalar(0.0, 0.0, 0.0);
	/**
	 * @brief Color white represented with cv::Scalar for RGB
	 * 
	 */
	const cv::Scalar SCALAR_WHITE = cv::Scalar(255.0, 255.0, 255.0);
	/**
	 * @brief Color yellow represented with cv::Scalar for RGB
	 * 
	 */
	const cv::Scalar SCALAR_YELLOW = cv::Scalar(0.0, 255.0, 255.0);
	/**
	 * @brief Color green represented with cv::Scalar for RGB
	 * 
	 */
	const cv::Scalar SCALAR_GREEN = cv::Scalar(0.0, 200.0, 0.0);
	/**
	 * @brief Color red represented with cv::Scalar for RGB
	 * 
	 */
	const cv::Scalar SCALAR_RED = cv::Scalar(0.0, 0.0, 255.0);

	/**
	 * @brief any detection below this percentage is considered inaccurate
	 * 
	 */
	float confThreshold = 0.5;
	/**
	 * @brief non maximum supppresion threshold
	 * 
	 */
	float nmsThreshold = 0.4;
	/**
	 * @brief Frame width size to be processed in DNN
	 * 
	 */
	int inpWidth = 256;
	/**
	 * @brief Frame height size to be processed in DNN
	 * 
	 */
	int inpHeight = 256;
	/**
	 * @brief Number of (possible) unique detections
	 * 
	 */
	int detectNum = 0;
	/**
	 * @brief list of classes loaded from EOIR/coco.names
	 * 
	 */
	std::vector<std::string> classes;
	/**
	 * @brief Video feed loaded and processed by OpenCV
	 * 
	 */
	cv::VideoCapture capVideo;
	/**
	 * @brief OpenCV's deep neural network 
	 * 
	 */
	Net net;
	/**
	 * @brief a maping of unique detection ids to information about the object
	 * 
	 */
	std::map<std::string, object> image_contents;
	/**
	 * @brief Current frame being processed by OpenCV
	 * 
	 */
	cv::Mat imgFrame1;
	/**
	 * @brief Deprecated Frame proceeding the current frame (for moving object detection)
	 * \deprecated
	 */
	cv::Mat imgFrame2;
	/**
	 * @brief Deprecated if true use the entire frame for objects, otherwise
	 * only run the moving objects through the DNN
	 * \deprecated
	 */
	bool scanEntireFrame = true;
	/**
	 * @brief Whether or not OpenCV is still processing data
	 * 
	 */
	bool running = false;
public:
	/**
	 * @brief load the class names from coco.names, load the model config from
	 * yolov3.cfg, load the weight of the network from yolov3.weights, pass the data
	 * to the neural network, load the video to be used for processing
	 * 
	 * @param VOID
	 *
	 * @return true if the video was loaded successfully
	 * @return false if the video did not load  
	 */
	bool init();
	/**
	 * @brief loop through each frame of the video, pass the data to 
	 * classifyEntire frame alongside the DNN instance
	 * 
	 * @param VOID
	 *
	 * @return VOID
	 */
	void run();
	/**
	 * @brief given two 2D points, calculate the distance between them
	 * using the distance formula
	 * 
	 * @param x1 - x value of point 1
	 * @param y1 - y value of point 1
	 * @param x2 - x value of point 2
	 * @param y2 - y value of point 2
	 *
	 * @return double - distance between 2 points
	 */
	double calculateDistance(int x1, int y1, int x2, int y2);
	/**
	 * @brief given an x and y value, determine if the object from the 
	 * current frame is close enough to the detection found in the last frame
	 * 
	 * @param x - x position of object in pixels
	 * @param y - y position of object in pixels
	 *
	 * @return string - empty if no object found, or unique id of object
	 * 
	 */
	string findObject(int x, int y);
	/**
	 * @brief Deprecated matche the current detected moving blobs to the 
	 * already exisiting ones
	 * 
	 * @param existingBlobs - vector of already processed blobs
	 * @param currentFrameBlobs - vector of current blobs
	 *
	 * @return VOID
	 * \deprecated
	 */
	void matchCurrentFrameBlobsToExistingBlobs(std::vector<Blob> &existingBlobs, std::vector<Blob> &currentFrameBlobs);
	/**
	 * @brief Deprecated given a single detected blob, add it to the vector of blobs for current frame
	 * 
	 * @param currentFrameBlob - current frame blob
	 * @param existingBlobs - vector of existing blobs
	 * @param intIndex - index of the blob relevant to the set of blobs detected
	 *
	 * @return VOID
	 * \deprecated
	 */
	void addBlobToExistingBlobs(Blob &currentFrameBlob, std::vector<Blob> &existingBlobs, int &intIndex);
	/**
	 * @brief Deprecated add a new blob to the set of existing blobs
	 * 
	 * @param currentFrameBlob - blob from the current frame
	 * @param existingBlobs - vectpr pf existing blobs
	 *
	 * @return VOID
	 * \deprecated
	 */
	void addNewBlob(Blob &currentFrameBlob, std::vector<Blob> &existingBlobs);
	/**
	 * @brief Deprecated calculate the distance (in pixels) between two points
	 * 
	 * @param point1 - OpenCv's point1
	 * @param point2 - OpenCv's point2
	 *
	 * @return double distance between the two points
	 * \deprecated
	 */
	double distanceBetweenPoints(cv::Point point1, cv::Point point2);
	/**
	 * @brief Deprecated classify the object by passing the frame to the dnn and adding the detection 
	 * to an unordered_map
	 * 
	 * @param blobs - current blobs (moving objects) in the frame
	 * @param frame - the entire frame currently being processed
	 * @param net - deep neural network configured in the init() function
	 * 
	 * @return VOID
	 * \deprecated
	 */
	void classify(const std::vector<Blob> &blobs, const cv::Mat &frame, dnn::Net &net);
	/**
	 * @brief Run OpenCV's yolov3 object detection on frame using the neural network
	 * configured in the init() function, and adding the detections to an unordered_map
	 * 
	 * @param frame - current frame being processed
	 * @param net - neural network configured in init() function
	 *
	 * @return VOID
	 */
	void classifyEntireFrame(const cv::Mat &frame, dnn::Net &net);
	/**
	 * @brief Used by classify(). Loop throught all detected moving objects
	 * identify the bounding boxes, and pass the data to drawPed for drawing 
	 * and add location information to detection unordered_map
	 *
	 * @param frame - current frame being processed
	 * @param out - output of objects detected by DNN
	 * @param x - in pixels, the location of blob
	 * @param y  - in pixel, the location of the blob
	 * @param w  - in pixel, the width of the blob
	 * @param h  - in pixel, the height of the blob
	 * @param processed_Blob - vector of detected blobs, with current one being added after processing
	 * 
	 * @return VOID
	 * \deprecated
	 */
	void postprocess(const cv::Mat& frame, const std::vector<cv::Mat>& out, int x, int y, int w, int h, blob_return &processed_Blob);
	/**
	 * @brief 
	 * 
	 * @param frame 
	 * @param out 
	 */
	void postprocessframe(const cv::Mat& frame, const std::vector<cv::Mat>& out);
	/**
	 * @brief Used by classify() and classifyEntireFrame(), this function adds the detection to the map
	 * and draws the detections, their label, and confidence on the frame
	 * 
	 * @param classId - classifcation id of the object
	 * @param conf - confidence of the object detected
	 * @param left - starting x value
	 * @param top - starting y value
	 * @param right - ending x value
	 * @param bottom - ending y value
	 * @param frame - current frame being processed
	 * 
	 * @return void
	 */
	void drawPred(int classId, float conf, int left, int top, int right, int bottom, const cv::Mat& frame);
	/**
	 * @brief Get the output names in order relevant to the detections
	 * 
	 * @param net - Neural network generating the detections
	 *
	 * @return vector<cv::String> classifications for each object, ordered in the same order as the detections
	 */
	vector<cv::String> getOutputsNames(const Net& net);
	/**
	 * @brief Get the detections map
	 * 
	 * @param VOID
	 * 
	 * @return std::map<std::string, object> map unique id to information of each detection
	 */
	std::map<std::string, object> getMap();
	/**
	 * @brief Used by EOIR to determine if OpenCV is still processing frames
	 * 
	 * @param VOID
	 *
	 * @return true if the loop to process the video is still going
	 */
	bool isRunning();


};
#endif
