#ifndef PROCESSOR_H
#define PROCESSOR_H

#include<string>
#include<vector>

#include "linux_parser.h"

class Processor {
 public:

    float Utilization();  

  // Declare any necessary private members
 private:

    long prevActiveJiffies{0};
    long prevTotalJiffies{0};
    long activeJiffies{0};
    long totalJiffies{0};

};

#endif