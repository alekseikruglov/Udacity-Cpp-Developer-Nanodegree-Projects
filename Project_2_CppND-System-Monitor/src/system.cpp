#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>


#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"
#include "format.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;


// Return the system's CPU
Processor& System::Cpu() 
{ 
    return cpu_; 
}

bool compareProcesses(Process &p1, Process &p2)
{
    //return p2.CpuUtilization() > p1.CpuUtilization();
    return p2 < p1;
}

// Return a container composed of the system's processes
vector<Process>& System::Processes() 
{ 
    
    //clear processes list
    System::processes_.clear();

    for(int currentPid : LinuxParser::Pids())
    {
        Process p(currentPid);      
        System::processes_.push_back(p);        
    }
    std::sort(System::processes_.begin(), System::processes_.end(), compareProcesses);
    
    return processes_; 
}

// Return the system's kernel identifier (string)
std::string System::Kernel() { return LinuxParser::Kernel(); }

// Return the system's memory utilization
float System::MemoryUtilization() 
{ 
    return LinuxParser::MemoryUtilization(); 
}

// Return the operating system name
std::string System::OperatingSystem() { return LinuxParser::OperatingSystem(); }

// Return the number of processes actively running on the system
int System::RunningProcesses() { return LinuxParser::RunningProcesses(); }

// Return the total number of processes on the system
int System::TotalProcesses() { return LinuxParser::TotalProcesses(); }

// Return the number of seconds since the system started running
long int System::UpTime() { return  LinuxParser::UpTime(); }

