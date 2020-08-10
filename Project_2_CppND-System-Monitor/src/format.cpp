#include <string>

#include "format.h"

using std::string;

// Helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) 
{ 
    int hours = seconds/3600;   //should be division without rest
    int minutes = (seconds-hours*3600)/60;
    int sec = seconds-hours*3600-minutes*60;

    string result = "";

    //hours
    if(hours < 10)
    {
        result = result + "0";
        result = result + std::to_string(hours);
    }else
    {
        result = result + std::to_string(hours);
    }
    result = result + ":";

    //minutes
    if(minutes < 10)
    {
        result = result + "0";
        result = result + std::to_string(minutes);
    }else
    {
        result = result + std::to_string(minutes);
    }
    result = result + ":";

    //minutes
    if(sec < 10)
    {
        result = result + "0";
        result = result + std::to_string(sec);
    }else
    {
        result = result + std::to_string(sec);
    }
 
    return result;     
}