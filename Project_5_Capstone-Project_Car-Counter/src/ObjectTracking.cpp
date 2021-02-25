
#include "ObjectTracking.h"

int ObjectTracking::updateObjectTracking(std::vector<std::unique_ptr<DetectedObject>> &currentDetectedObjects)
{

    int objCounterThisFrame = 0;

    if(_livingObjects.size() == 0)
    {
        for(auto &theObj : currentDetectedObjects)
        {
            theObj->setIsTracked(true);
            _livingObjects.emplace_back(std::move(theObj));
        }
    }
    else
    {
        //match new Objects to existing objects + add new objects to _livingObjects
        if(currentDetectedObjects.size() > 0)
        {
            matchNewObjectsToPreviousFrames(currentDetectedObjects);
        }
         
        //check if Objects passed the counting line -> increase counter
        for(auto &livingObj : _livingObjects)
        {
            printObjectIformation(livingObj);           
            if(livingObj->checkCountingLineIsPassed())
            {
                objCounterThisFrame++;
            }
        }

        //remove already counted objects from _livingObjects
        this->_livingObjects.erase(std::remove_if(this->_livingObjects.begin(), this->_livingObjects.end(), [](std::unique_ptr<DetectedObject> &theObj){
            return theObj->getIsCounted();
        }), this->_livingObjects.end());

        //delete objects from _livingObjects, which are not tracked any more (>= N times not updated)
        this->_livingObjects.erase(std::remove_if(this->_livingObjects.begin(), this->_livingObjects.end(), [](std::unique_ptr<DetectedObject> &theObj){
            return theObj->checkObjectIsNotUpdatedAnyMore();
        }), this->_livingObjects.end());

    }

    return objCounterThisFrame;
    
}

void ObjectTracking::matchNewObjectsToPreviousFrames(std::vector<std::unique_ptr<DetectedObject>> &currentDetectedObjects)
{

    //find closest current objects to existing object
    for(auto &livingObj : _livingObjects)
    {
        if(currentDetectedObjects.size() == 0)
        {
            break;
        }
        //sort currentDetectedObjects, that element with min distance to theObj is the last element of the list
        std::sort(currentDetectedObjects.begin(), currentDetectedObjects.end(), [this, &livingObj](std::unique_ptr<DetectedObject> &obj1, std::unique_ptr<DetectedObject> &obj2){ 
            return this->calculateDistanceBetweenPoints(obj1->getCenterPosition(), livingObj->getCenterPosition()) > this->calculateDistanceBetweenPoints(obj2->getCenterPosition(), livingObj->getCenterPosition());
        });

        double distance = 0;
        distance = calculateDistanceBetweenPoints(currentDetectedObjects.back()->getCenterPosition(), livingObj->getCenterPosition());
        if(distance < livingObj->getRectDiagonal()*0.4)
        {
            livingObj->addToPreviousCenters(livingObj->getCenterPosition());
            livingObj->setContour(currentDetectedObjects.back()->getContour());
            livingObj->update();
            currentDetectedObjects.pop_back();
        }
        else
        {
            //if no objects close enough found -> increase timesNotUpdated
            livingObj->increaseTimesNotUpdated();
        }
    }

    //if any current objects are not mutched to the previous objects - add this objects as new living obects
    if(currentDetectedObjects.size() > 0)
    {
        for(auto &curObj : currentDetectedObjects)
        {
            curObj->setIsTracked(true);
            curObj->setTimesNotUpdated(0);
            _livingObjects.emplace_back(std::move(curObj));
        }
    }

}

double ObjectTracking::calculateDistanceBetweenPoints(cv::Point &p1, cv::Point &p2)
{
    int intX = abs(p1.x - p2.x);
    int intY = abs(p1.y - p2.y);

    return(sqrt(pow(intX, 2) + pow(intY, 2)));
}

void ObjectTracking::drawTracking(cv::Mat &img, std::string windowName)
{
    for(auto &theObj : this->_livingObjects)
    {
        if(!theObj->getXmlParams()->getShowObjectTracking())
        {
            break;
        }
        
        for(auto &thePos : theObj->getPreviousCenters())
        {
            cv::circle(img, thePos, 5, cv::Scalar(0.0, 0.0, 255.0),2);     
        }
        if(theObj->getXmlParams()->getShowObjectNumbers())
        {
            cv::putText(img, std::to_string(theObj->getThisObjId()), theObj->getCenterPosition(), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255,0,0), 3);
        }       
    }          
}

void ObjectTracking::printObjectIformation(std::unique_ptr<DetectedObject> &obj)
{
    if(obj->getXmlParams()->getPrintObjectInfo())
    {
        std::cout << "id: " << obj->getThisObjId();
        std::cout << "||x: " << obj->getCenterPosition().x;
        std::cout << "||y: " << obj->getCenterPosition().y;
        if(obj->getPreviousCenters().size() > 0)
        {
            std::cout << "||prev x: " << obj->getPreviousCenters().back().x;
            std::cout << "||prev y: " << obj->getPreviousCenters().back().y;
        }
        else
        {
            std::cout << "||prev x: " << "no";
            std::cout << "||prev y: " << "no";
        }
        
        std::cout << "||area: " << obj->getBoundingRect().area();
        std::cout << "||w: " << obj->getBoundingRect().width;
        std::cout << "||h: " << obj->getBoundingRect().height;
        std::cout << "||diag: " << obj->getRectDiagonal();
        std::cout << "||r: " << obj->getAspectRatio();
        std::cout << std::endl;  
    }
    
}