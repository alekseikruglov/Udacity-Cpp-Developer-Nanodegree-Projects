#ifndef OBJECT_TRACKING
#define OBJECT_TRACKING

#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>


#include "DetectedObject.h"

class ObjectTracking
{
public:

    int updateObjectTracking(std::vector<std::unique_ptr<DetectedObject>> &currentDetectedObjects);
    void matchNewObjectsToPreviousFrames(std::vector<std::unique_ptr<DetectedObject>> &currentDetectedObjects);
    double calculateDistanceBetweenPoints(cv::Point &p1, cv::Point &p2);

    void drawTracking(cv::Mat &img, std::string windowName);

    void printObjectIformation(std::unique_ptr<DetectedObject> &obj);

private:
    std::vector<std::unique_ptr<DetectedObject>> _livingObjects;    //detected in previous frames + current objects, which are still tracked 

};

#endif    // OBJECT_TRACKING