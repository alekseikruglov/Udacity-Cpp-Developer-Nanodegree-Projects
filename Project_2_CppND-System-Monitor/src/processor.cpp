#include "processor.h"


// Return the aggregate CPU utilization
float Processor::Utilization() 
{ 

    float CPU_Percentage  = 0;
    
    prevActiveJiffies = activeJiffies;
    prevTotalJiffies = totalJiffies;

    activeJiffies = LinuxParser::ActiveJiffies();
    totalJiffies = LinuxParser::Jiffies();

    float totald = 0;
    float actived = 0;

    totald = (float)(abs(totalJiffies - prevTotalJiffies));
    actived = (float)(abs(activeJiffies - prevActiveJiffies));

    if(totald != 0)
    {
        CPU_Percentage = actived / totald;
    }

    return CPU_Percentage;

}