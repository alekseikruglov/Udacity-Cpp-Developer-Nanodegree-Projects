#ifndef VIDEO_PROCESSING
#define VIDEO_PROCESSING

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/video/video.hpp>

#include <string>
#include <vector>
#include <memory>

#include "DetectedObject.h"
#include "ObjectTracking.h"
#include "ParsingXML.h"


class VideoProcessing
{
public:
    VideoProcessing(std::string pathToVideo);
    void makeFrameDifference();
    void makeThreshold(int threshold);
    void makeErode(int structuringElementSize, int dilateNum);
    
    void findValidObjects(std::vector<std::unique_ptr<DetectedObject>> &objectsVector);
    void findContours(cv::Mat &contours, std::vector<std::unique_ptr<DetectedObject>> &detectedObjects);

    void drawContours(cv::Mat& contours, std::string windowName);
    void drawRectangles(std::vector<std::unique_ptr<DetectedObject>> &detectedObjects, std::string windowName);

    void startVideoProcessing();
private:
    std::string _pathToVideo;
    std::unique_ptr<cv::VideoCapture> _capVideo;
    std::unique_ptr<ObjectTracking> _objTracking;
    std::unique_ptr<ParsingXML> _parameters;
    cv::Mat _frame1;
    cv::Mat _frame2;
    cv::Mat _frameDifference;
    cv::Mat _frameThreshold;

    int _carCounter{0};
};




#endif    // VIDEO_PROCESSING