#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "linux_parser.h"
#include "process.h"

using std::string;
using std::to_string;
using std::vector;

// TODO: Return this process's ID
int Process::Pid() { return Process::Pid_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { 
    // get active jiffies
    // retrieve starttime from the call Process::Uptime
    // retrieve uptime from linuxparser
    long activeJiffies = LinuxParser::ActiveJiffies(Process::Pid_);
    long starttime = Process::UpTime();
    long uptime = LinuxParser::UpTime();
    auto actual_uptime = uptime - starttime;
    auto activetime = activeJiffies / (sysconf(_SC_CLK_TCK));

    float cpuutil = ((float)activetime / actual_uptime);
    // actual_uptime = uptime - starttime
    // totaltime in sec / actual_uptime


    return cpuutil; 
}

// TODO: Return the command that generated this process
string Process::Command() { return LinuxParser::Command(Process::Pid_); }

// TODO: Return this process's memory utilization
string Process::Ram() const{ return LinuxParser::Ram(Process::Pid_); }

// TODO: Return the user (name) that generated this process
string Process::User() {
  return LinuxParser::User(Process::Pid_);  // TODO: need to pass uid here
  // return string();
}

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime(Process::Pid_); }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const {
   auto RamUtil1 = std::stol(Process::Ram());
   auto RamUtil2 = std::stol(a.Ram());
   
   return (RamUtil2 < RamUtil1) ; 
}

void Process::Pid(int id) { Process::Pid_ = id; }