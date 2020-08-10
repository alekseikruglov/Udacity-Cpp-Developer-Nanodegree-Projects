#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// Read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// Read data from the filesystem
string LinuxParser::Kernel() {
  string os, version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// To use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// Read and return the system memory utilization
float LinuxParser::MemoryUtilization() 
{ 
  string keyWord;
  float number;
  float MemTotal = 0;
  float MemAvailable = 0;

  string line;
  std::ifstream stream(kProcDirectory + kMeminfoFilename);
  if (stream.is_open()) {
    while(std::getline(stream, line))
    {
      std::istringstream linestream(line);
      linestream >> keyWord >> number;

      if(keyWord == "MemTotal:")
      {
        MemTotal = number;
      }
      if(keyWord == "MemAvailable:")
      {
        MemAvailable = number;
      }
    }
    
    return MemAvailable / MemTotal; 
  }

  return 0;
}

// Read and return the system uptime
long LinuxParser::UpTime() 
{ 

  float time1;
  float time2;
  string line;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);

    linestream >> time1 >> time2;

    return long(time1); 
  }
  return 0;
}

// Read and return the number of jiffies for the system
long LinuxParser::Jiffies() 
{ 
  long result = 0;
  vector<string> strCpuInfo = LinuxParser::CpuUtilization();
  
   result = atol(strCpuInfo[kUser_].c_str()) - atol(strCpuInfo[kGuest_].c_str()) + atol(strCpuInfo[kNice_].c_str()) - atol(strCpuInfo[kGuestNice_].c_str()) + 
                atol(strCpuInfo[kSystem_].c_str()) + atol(strCpuInfo[kIdle_].c_str()) + atol(strCpuInfo[kIOwait_].c_str()) +
                atol(strCpuInfo[kIRQ_].c_str()) + atol(strCpuInfo[kSoftIRQ_].c_str()) + atol(strCpuInfo[kSteal_].c_str());
  
  return result; 
}

// Read and return the number of active jiffies for a PID
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() 
{ 
  long result = 0;
  vector<string> strCpuInfo = LinuxParser::CpuUtilization();
  
   result = atol(strCpuInfo[kUser_].c_str()) - atol(strCpuInfo[kGuest_].c_str()) + atol(strCpuInfo[kNice_].c_str()) - atol(strCpuInfo[kGuestNice_].c_str()) + 
                atol(strCpuInfo[kSystem_].c_str()) +
                atol(strCpuInfo[kIRQ_].c_str()) + atol(strCpuInfo[kSoftIRQ_].c_str()) + atol(strCpuInfo[kSteal_].c_str());
  
  return result; 
}

// Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() 
{ 
  long result = 0;
  vector<string> strCpuInfo = LinuxParser::CpuUtilization();
  
  result = atol(strCpuInfo[kIdle_].c_str()) + atol(strCpuInfo[kIOwait_].c_str());
  
  return result; 
}

// Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() 
{ 

  vector<string> result;
  string word;
  string line;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    
    //make stream from this line
    std::istringstream linestream(line);

    while(linestream >> word)
    {
      if(word != "cpu")
      {
        result.push_back(word);
      }
    }
  }  
  return result; 
}

// Read and return the total number of processes
int LinuxParser::TotalProcesses() 
{ 
  string keyWord;
  int number;
  string line;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);

      linestream >> keyWord >> number;
      if(keyWord == "processes")  
      {
        return number;
      }
    }

  }
  return 0;
}

// Read and return the number of running processes
int LinuxParser::RunningProcesses() 
{ 
  string keyWord;
  int number;
  string line;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);

      linestream >> keyWord >> number;
      if(keyWord == "procs_running")  
      {
        return number;
      }
    }

  }
  return 0; 
}

// Read and return the command associated with a process
string LinuxParser::Command(int pid) 
{ 
  string line;
  std::ifstream stream(kProcDirectory + to_string(pid) + kCmdlineFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    return line;
  }
  return string();
}

// Read and return the memory used by a process
string LinuxParser::Ram(int pid) 
{ 
  string keyWord;
  string number;
  string line;
  std::ifstream stream(kProcDirectory + to_string(pid) + kStatusFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {

      std::istringstream linestream(line);

      linestream >> keyWord >> number;
      if(keyWord == "VmSize:")  
      {
        return number;
      }
    }
  }
  return string();
}



vector<string> LinuxParser::processCpu(int pid)
{
  vector<string> result = {};

  string word;
  //int counter = 1;

  string line;
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);

    std::istringstream linestream(line);

    while(linestream >> word)
    {
      result.push_back(word);
    
    }

  }

  return result;
}

// Read and return the user ID associated with a process
int LinuxParser::Uid(int pid) 
{ 
  string keyWord;
  int id;
  string line;
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatusFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {

      std::istringstream linestream(line);

      linestream >> keyWord >> id;
      if(keyWord == "Uid:")  
      {
        return id;
      }
    }
  }
  return 0;
}

// Read and return the user associated with a process
string LinuxParser::User(int uid) 
{
  string userName;
  string x;
  int id;
  string line;
  std::ifstream stream(kPasswordPath);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');

      std::istringstream linestream(line);

      linestream >> userName >> x >> id;
      if(id == uid)  
      {
        return userName;
      }
    }
  }
  return string();
}

// Read and return the uptime of a process
long LinuxParser::UpTime(int pid) 
{ 
  long result = 0;

  string word;
  int counter = 1;

  string line;
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);

    std::istringstream linestream(line);

    while(linestream >> word)
    {
      if(counter == 22)
      {
        result = atol(word.c_str());
        break;
      }
      counter++;
    }

  }

  return result;

}