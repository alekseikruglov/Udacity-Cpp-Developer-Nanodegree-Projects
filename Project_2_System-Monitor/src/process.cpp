#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"


using std::string;
using std::to_string;
using std::vector;

//Constructor
Process::Process(int pid)
{
    Process::setPid(pid);
   
    Process::setUser(LinuxParser::User(LinuxParser::Uid(pid)));
    
    Process::setRam(LinuxParser::Ram(pid));
    
    Process::setUpTime(LinuxParser::UpTime() - LinuxParser::UpTime(pid)/sysconf(_SC_CLK_TCK));
    
    Process::setCommand(LinuxParser::Command(pid));

    Process::setCpuUtilization(LinuxParser::processCpu(pid));
}

// Return this process's ID
int Process::Pid() { return Process::pid; }

// Return this process's CPU utilization
float Process::CpuUtilization() { return Process::cpuUtilization; }

// Return the command that generated this process
string Process::Command() { return Process::command; }

// Return this process's memory utilization
string Process::Ram() { return Process::ram; }

// Return the user (name) that generated this process
string Process::User() { return Process::user; }

// Return the age of this process (in seconds)
long int Process::UpTime() { return Process::upTime; }

// Overload the "less than" comparison operator for Process objects
bool Process::operator<(Process const& a) const 
{ 

    if(this->cpuUtilization < a.cpuUtilization)
    {
        return true; 
    }else
    {
        return false; 
    }
    
}

void Process::setUpTime(long int ut)
{
    Process::upTime = ut;
}

void Process::setCpuUtilization(std::vector<string> strCpuUt)
{

    //check if strCpiUt is not empty
    if(strCpuUt.size() != 0)   
    {
 
        long uptime = LinuxParser::UpTime(); //system upTime without params, overloading!
        float utime = atof(strCpuUt[13].c_str());
        float stime = atof(strCpuUt[14].c_str());
        float cutime = atof(strCpuUt[15].c_str());
        float cstime = atof(strCpuUt[16].c_str());
        float starttime = atof(strCpuUt[21].c_str());
        long Hertz = sysconf(_SC_CLK_TCK);

        //calculation
        float total_time = utime + stime;
        total_time = total_time + cutime + cstime;
        float seconds = 0;
        if(Hertz > 0)
        {
            seconds = uptime - (starttime / Hertz);
            if((seconds > 0))
            {
                if(((total_time / Hertz) / seconds) < 1)
                {
                    Process::cpuUtilization = ((total_time / Hertz) / seconds);
                }else
                {
                    Process::cpuUtilization = 1;
                }              
            }
        }   
    }//check if strCpiUt is not empty
}

void Process::setRam(std::string r) 
{
    long longRam = atol(r.c_str());
    //convert to MB
    longRam = longRam/1024;

    std::string strRam = std::to_string(longRam);

    Process::ram = strRam;
}