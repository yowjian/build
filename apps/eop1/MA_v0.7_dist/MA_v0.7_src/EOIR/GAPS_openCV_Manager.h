#pragma once
#ifndef GAPS_OPENCV_MANAGER_H
#define GAPS_OPENCV_MANAGER_H
#include <map>
#include <vector>
#include <string>
#include "Blob.h"

struct GAPS_opencv_Return
{
     double image_Confidence;
     std::vector<std::pair<double, double>> centerPositions;
};

std::map<std::string, GAPS_opencv_Return> run_GAPS_Video_Anaylsis(void);
void print_GAPS_openCV_Return(std::map<std::string, GAPS_opencv_Return> image_Values);
void update_To_Ground_Truth(std::map<std::string, GAPS_opencv_Return> &image_Values, double lat, double longitude);

#endif
