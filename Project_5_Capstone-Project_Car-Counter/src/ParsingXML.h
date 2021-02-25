#ifndef PARSING_XML
#define PARSING_XML

#include <iostream>

#include <vector>
#include <string>

#include "pugixml.hpp"


class ParsingXML
{
public:
    ParsingXML(std::string strPath);
    int getFrameThreshold(){return _frameThreshold;};
    int getErodeStructuringElementSize(){return _erodeStructuringElementSize;};
    int getDilateCyclesNumber(){return _dilateCyclesNumber;};
    int getValidObjArea(){return _validObjArea;};
    int getValidObjWidth(){return _validObjWidth;};
    int getValidObjHeight(){return _validObjHeight;};
    double getAspectRatio(){return _aspectRatio;};
    int getCountingLinePositionX1(){return _countingLinePositionX1;};
    int getCountingLinePositionX2(){return _countingLinePositionX2;};
    int getCountingLinePositionY1(){return _countingLinePositionY1;};
    int getCountingLinePositionY2(){return _countingLinePositionY2;};
    int getNotUpdatedMaxNum(){return _notUpdatedMaxNum;};
    bool getPrintObjectInfo(){return _printObjectInfo;};
    bool getShowObjectNumbers(){return _showObjectNumbers;};
    bool getShowObjectTracking(){return _showObjectTracking;};

    

private:
    pugi::xml_document _doc;
    int _frameThreshold{0};
   	int _erodeStructuringElementSize{0};
	int _dilateCyclesNumber{0};
	int _validObjArea{0};
	int _validObjWidth{0};
	int _validObjHeight{0};
    double _aspectRatio{0};
	int _countingLinePositionX1{0};
	int _countingLinePositionX2{0};
	int _countingLinePositionY1{0};
	int _countingLinePositionY2{0};
    int _notUpdatedMaxNum{0};
    bool _printObjectInfo{false};
    bool _showObjectNumbers{false};
    bool _showObjectTracking{false};
};


#endif    // PARSING_XML