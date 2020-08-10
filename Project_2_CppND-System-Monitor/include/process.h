#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include <vector>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
 //Constructor
  //Process();
  Process(int pid);
  int Pid();                               
  std::string User();                      
  std::string Command();                  
  float CpuUtilization();                  
  std::string Ram();                       
  long int UpTime();                       
  bool operator<(Process const& a) const;  

  //Setter:
    void setPid(int thePid) {pid =thePid;}
    void setUser(std::string u){user = u;}
    void setCpuUtilization(std::vector<std::string> strCpuUt);
    void setRam(std::string r);
    void setUpTime(long int ut);
    void setCommand(std::string c){command = c;}


  //  Declare any necessary private members
 private:
    int pid{0};
    std::string user{""};
    float cpuUtilization{0};
    std::string ram{""};
    long int upTime{0};
    std::string command{""};

};

#endif