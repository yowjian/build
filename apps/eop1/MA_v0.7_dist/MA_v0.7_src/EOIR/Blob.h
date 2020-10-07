#pragma once


#ifndef MY_BLOB
#define MY_BLOB

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <vector>

class Blob {
public:
     std::vector<cv::Point> currentContour;

     cv::Rect currentBoundingRect;

     std::vector<cv::Point> centerPositions;

     double dblCurrentDiagonalSize;
     double dblCurrentAspectRatio;

     bool blnCurrentMatchFoundOrNewBlob;

     bool blnStillBeingTracked;

     std::vector<std::string> blob_Class;

     std::vector<float> blob_Confidence_Avg;

     int intNumOfConsecutiveFramesWithoutAMatch;

     cv::Point predictedNextPosition;

     Blob(std::vector<cv::Point> _contour);
     void predictNextPosition(void);

};

#endif
