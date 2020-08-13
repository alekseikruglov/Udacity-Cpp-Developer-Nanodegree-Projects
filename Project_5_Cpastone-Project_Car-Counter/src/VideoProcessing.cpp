
#include "VideoProcessing.h"



VideoProcessing::VideoProcessing(std::string pathToVideo) : _pathToVideo(pathToVideo)
{
    _capVideo = std::make_unique<cv::VideoCapture>(_pathToVideo);

    if(!_capVideo->isOpened())
    {
        std::cout << "Error reading video!" << std::endl;
    }
    else
    {
        _capVideo->read(_frame1);
        _capVideo->read(_frame2);
    }

    _objTracking = std::make_unique<ObjectTracking>();
    DetectedObject::objId = 0;  //static variable to make unique object-ids

    _parameters = std::make_unique<ParsingXML>("../data/data.xml");
    
}

void VideoProcessing::startVideoProcessing()
{
    while(_capVideo->isOpened())
    {
        //make copy of frames, which stay without processing
        cv::Mat copyFrame2 = _frame2.clone();

        makeFrameDifference();
        makeThreshold(_parameters->getFrameThreshold());
        makeErode(_parameters->getErodeStructuringElementSize(), _parameters->getDilateCyclesNumber());
        //cv::imshow("Threshold", _frameThreshold);

        std::vector<std::unique_ptr<DetectedObject>> validObj; 

        findValidObjects(validObj);
        cv::Mat contours(_frameThreshold.size(), CV_8UC3, cv::Scalar(0.0, 0.0, 0.0));
        findContours(contours, validObj);

        //drawContours(contours, "Contours");
        
        drawRectangles(validObj, "Video");

        cv::line(_frame2, cv::Point(_parameters->getCountingLinePositionX1(), _parameters->getCountingLinePositionY1()), cv::Point(_parameters->getCountingLinePositionX2(), _parameters->getCountingLinePositionY2()), cv::Scalar(0,0,255), 3);
        this->_carCounter += _objTracking->updateObjectTracking(validObj);
        _objTracking->drawTracking(_frame2, "Video");
        cv::putText(_frame2, std::to_string(this->_carCounter), cv::Point(50, 100), cv::FONT_HERSHEY_SIMPLEX, 3, cv::Scalar(255,0,0), 3);

        cv::imshow("Video", _frame2);

        if ((_capVideo->get(cv::CAP_PROP_POS_FRAMES) + 1) < _capVideo->get(cv::CAP_PROP_FRAME_COUNT)) {
            _frame1 = copyFrame2.clone();
            _capVideo->read(_frame2);
        } else {
            std::cout << "end of video\n";
            break;
        }
        
        //cv::waitKey(0);
        cv::waitKey(1);
    }
}

void VideoProcessing::makeFrameDifference()
{
    //copy frames for processing
    cv::Mat copyFrame1 = _frame1.clone();
    cv::Mat copyFrame2 = _frame2.clone();
    cv::cvtColor(copyFrame1, copyFrame1, cv::COLOR_BGR2GRAY);
    cv::cvtColor(copyFrame2, copyFrame2, cv::COLOR_BGR2GRAY);

    cv::GaussianBlur(copyFrame1, copyFrame1, cv::Size(5,5), 0);
    cv::GaussianBlur(copyFrame2, copyFrame2, cv::Size(5,5), 0);

    cv::absdiff(copyFrame1, copyFrame2, _frameDifference);
}

void VideoProcessing::makeThreshold(int threshold)
{
    cv::threshold(_frameDifference, _frameThreshold, threshold, 255, cv::THRESH_BINARY);
}

void VideoProcessing::makeErode(int structuringElementSize, int dilateNum)
{
    cv::Mat structuringElement = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(structuringElementSize, structuringElementSize));

    for(int i = 0; i < dilateNum; i++)
    {
        cv::dilate(_frameThreshold, _frameThreshold, structuringElement);
        cv::dilate(_frameThreshold, _frameThreshold, structuringElement);
    }
    
    cv::erode(_frameThreshold, _frameThreshold, structuringElement);
}

void VideoProcessing::findValidObjects(std::vector<std::unique_ptr<DetectedObject>> &objectsVector)
{
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(_frameThreshold, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    cv::Mat imgContours(_frameThreshold.size(), CV_8UC3, cv::Scalar(0.0, 0.0, 0.0));
    cv::drawContours(imgContours, contours, -1, cv::Scalar(0.0, 0.0, 255.0), 1);

    std::vector<std::vector<cv::Point> > convexHulls(contours.size());
    for (int i = 0; i < contours.size(); i++) 
    {
        cv::convexHull(contours[i], convexHulls[i]);
        
        std::unique_ptr<DetectedObject> currentDetectdObj = std::make_unique<DetectedObject>(convexHulls[i], _parameters.get());
        if(currentDetectdObj->checkDetectedObjectIsValid())   //check if detected contour is big enough to be a car
        {
            objectsVector.emplace_back(std::move(currentDetectdObj));
        }      
    }
}

void VideoProcessing::findContours(cv::Mat &contours, std::vector<std::unique_ptr<DetectedObject>> &detectedObjects)
{
    std::vector<std::vector<cv::Point>> validConvexHulls;
    for(auto &currentDetectedObj : detectedObjects)
    {
        validConvexHulls.emplace_back(currentDetectedObj->getContour());
    }

    cv::drawContours(contours, validConvexHulls, -1, cv::Scalar(0.0, 0.0, 255.0), 1);  
}

void VideoProcessing::drawContours(cv::Mat &contours, std::string windowName)
{    
    cv::imshow(windowName, contours);
}

void VideoProcessing::drawRectangles(std::vector<std::unique_ptr<DetectedObject>> &detectedObjects, std::string windowName)
{
    //draw rectangles over detected contours
    for(auto &currentDetectedObj : detectedObjects)
    {
        cv::rectangle(_frame2, currentDetectedObj->getBoundingRect(), cv::Scalar(0.0, 255.0, 0.0), 2);
    }
}











