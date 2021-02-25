#include "ParsingXML.h"

ParsingXML::ParsingXML(std::string strPath)
{
    pugi::xml_document _doc;
    pugi::xml_parse_result result = _doc.load_file("../data/data.xml");
    std::cout << "Load result: " << result.description() <<std::endl<<std::endl;  

    _frameThreshold = std::stoi(_doc.child("parameters").child("frameThreshold").child_value());
   	_erodeStructuringElementSize = std::stoi(_doc.child("parameters").child("erodeStructuringElementSize").child_value());
	_dilateCyclesNumber = std::stoi(_doc.child("parameters").child("dilateCyclesNumber").child_value());
	_validObjArea = std::stoi(_doc.child("parameters").child("validObjArea").child_value());
	_validObjWidth = std::stoi(_doc.child("parameters").child("validObjWidth").child_value());
	_validObjHeight = std::stoi(_doc.child("parameters").child("validObjHeight").child_value());
	_aspectRatio = std::stod(_doc.child("parameters").child("aspectRatio").child_value());
	_countingLinePositionX1 = std::stoi(_doc.child("parameters").child("countingLinePositionX1").child_value());
	_countingLinePositionX2 = std::stoi(_doc.child("parameters").child("countingLinePositionX2").child_value());
	_countingLinePositionY1 = std::stoi(_doc.child("parameters").child("countingLinePositionY1").child_value());
	_countingLinePositionY2 = std::stoi(_doc.child("parameters").child("countingLinePositionY2").child_value());
	_notUpdatedMaxNum = std::stoi(_doc.child("parameters").child("notUpdatedMaxNum").child_value());
	
	if(std::stoi(_doc.child("parameters").child("printObjectInfo").child_value()) == 1)
	{
		_printObjectInfo = true;
	}
	else
	{
		_printObjectInfo = false;
	}

	if(std::stoi(_doc.child("parameters").child("showObjectNumbers").child_value()) == 1)
	{
		_showObjectNumbers = true;
	}
	else
	{
		_showObjectNumbers = false;
	}

	if(std::stoi(_doc.child("parameters").child("showObjectTracking").child_value()) == 1)
	{
		_showObjectTracking = true;
	}
	else
	{
		_showObjectTracking = false;
	}

}
