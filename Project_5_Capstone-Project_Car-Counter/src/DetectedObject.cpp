
#include "DetectedObject.h"

int DetectedObject::objId = 0;

DetectedObject::DetectedObject(std::vector<cv::Point> &contour, ParsingXML *parameters)
{
    this->_contour = contour;
    this->_params = parameters;
    this->update ();
   
    objId++;
    this->_thisObjId = objId;
}

void DetectedObject::update()
{
    this->_boundingRect = cv::boundingRect(_contour);
    this->_centerPosition.x = (this->_boundingRect.x + this->_boundingRect.x + this->_boundingRect.width)/2;
    this->_centerPosition.y = (this->_boundingRect.y + this->_boundingRect.y + this->_boundingRect.height)/2;
    this->_rectDiagonal = sqrt(pow(this->_boundingRect.width, 2) + pow(this->_boundingRect.height, 2));
    this->_aspectRatio = (double)this->_boundingRect.width / (double)this->_boundingRect.height;
}

bool DetectedObject::checkDetectedObjectIsValid()
{
    bool result = true;
    if(this->_boundingRect.area() < this->_params->getValidObjArea())
    {
        result = false;
    }

    if(this->_boundingRect.width < this->_params->getValidObjWidth())
    {
        result = false;
    }

    if(this->_boundingRect.height < this->_params->getValidObjHeight())
    {
        result = false;
    }

    if( this->_aspectRatio < this->_params->getAspectRatio() )
    {
        result = false;
    }

    return result;
}

bool DetectedObject::checkCountingLineIsPassed()
{
    if((_previousCenters.size() > 0) && (_centerPosition.y >= this->_params->getCountingLinePositionY1()) && (_previousCenters.back().y < this->_params->getCountingLinePositionY1()))
    {
        this->_isTracked = false;
        this->_isCounted = true;
        return true;
    }
    else
    {
        return false;
    }
}

void DetectedObject::addToPreviousCenters(cv::Point &pos)
{
    _previousCenters.push_back(pos);
}

bool DetectedObject::checkObjectIsNotUpdatedAnyMore()
{
    if(this->_timesNotUpdated >= this->_params->getNotUpdatedMaxNum())
    {
        return true;
    }
    else
    {
        return false;
    }
}
