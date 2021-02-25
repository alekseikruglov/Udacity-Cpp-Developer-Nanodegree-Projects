#ifndef DETECTED_OBJECT
#define DETECTED_OBJECT

#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

#include <vector>

#include "ParsingXML.h"

class DetectedObject
{
public:
    static int objId;

    DetectedObject(std::vector<cv::Point> &_contour, ParsingXML *parameters);
    bool checkDetectedObjectIsValid();
    void increaseTimesNotUpdated(){_timesNotUpdated++;};
    bool checkCountingLineIsPassed();
    void addToPreviousCenters(cv::Point &pos);
    void update();
    bool checkObjectIsNotUpdatedAnyMore();

    //get/set
    int getThisObjId(){return _thisObjId;};
    std::vector<cv::Point> &getContour(){return _contour;};
    void setContour(std::vector<cv::Point> &cont){_contour = cont;};
    cv::Rect &getBoundingRect(){return _boundingRect;};
    void setBoundingRect(cv::Rect &br){_boundingRect = br;};
    cv::Point &getCenterPosition(){return _centerPosition;};
    void setCenterPosition(cv::Point &pos){_centerPosition = pos;};
    double getRectDiagonal(){return _rectDiagonal;};
    void setRectDiagonal(double rd){_rectDiagonal = rd;};
    std::vector<cv::Point> &getPreviousCenters(){return _previousCenters;};
    bool getIsTracked(){return _isTracked;};
    void setIsTracked(bool trackingState){_isTracked = trackingState;};
    int getTimesNotUpdated(){return _timesNotUpdated;};
    void setTimesNotUpdated(int num){_timesNotUpdated = num;};
    bool getIsCounted(){return _isCounted;};
    void setIsCounted(bool state){_isCounted = state;};
    double getAspectRatio(){return _aspectRatio;};
    ParsingXML *getXmlParams(){return _params;};

private:
    int _thisObjId{0};
    std::vector<cv::Point> _contour;
    cv::Rect _boundingRect;
    cv::Point _centerPosition;
    double _rectDiagonal{0};
    double _aspectRatio{0};

    int _timesNotUpdated {0};   //how many frames this object is not updated 

    bool _isTracked{true};
    bool _isCounted{false};

    std::vector<cv::Point> _previousCenters;
    ParsingXML *_params;    //handle to parameters from XML

};





#endif    // DETECTED_OBJECT