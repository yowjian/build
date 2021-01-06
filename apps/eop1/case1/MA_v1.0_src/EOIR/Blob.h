#pragma once


#ifndef MY_BLOB
#define MY_BLOB

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <vector>
/**
* @brief – Class responsible for moving object blob data
* 
*
* @author – Original Author - OpenCV Dev Team
* @author – Last Edited By - Mases Krikorian
* @date – 8/31/2020
*
* @details – Information about a blob and the relating functions
* to determine if an object has been detect, moving, etc
*/
class Blob {
public:
     /**
      * @brief vector of points to hold current contour
      * 
      */
     std::vector<cv::Point> currentContour;
     /**
      * @brief a cv rectangle object holding information 
      * as to where the object is in a given rectangle area
      * 
      */
     cv::Rect currentBoundingRect;
     /**
      * @brief All center positions of the blobs
      * 
      */
     std::vector<cv::Point> centerPositions;
     /**
      * @brief diagonal size of blob
      * 
      */
     double dblCurrentDiagonalSize;
     /**
      * @brief aspect ratio of blob
      * 
      */
     double dblCurrentAspectRatio;
     /**
      * @brief true if match has been found
      * 
      */
     bool blnCurrentMatchFoundOrNewBlob;
     /**
      * @brief true if blob is still being tracked
      * 
      */
     bool blnStillBeingTracked;
     /**
      * @brief blob classes detected
      * 
      */
     std::vector<std::string> blob_Class;
     /**
      * @brief average confidence of blob
      * 
      */
     std::vector<float> blob_Confidence_Avg;
     /**
      * @brief if the object is not detected or tracked 
      * consecutively, this number will increase
      * 
      */
     int intNumOfConsecutiveFramesWithoutAMatch;
     /**
      * @brief base on previous position and speed, where the next 
      * position might be
      * 
      */
     cv::Point predictedNextPosition;
     /**
      * @brief Construct a new Blob object
      * 
      * @param _contour - vector of all the contours
      */
     Blob(std::vector<cv::Point> _contour);
     /**
      * @brief predict next position of the blob
      *
      * @param VOID
      * 
      * @return VOID
      */
     void predictNextPosition(void);

};

#endif
