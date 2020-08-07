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

// TODO: Return this process's ID
int Process::Pid() { return Process::Pid_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { return 0; }

// TODO: Return the command that generated this process
string Process::Command() { return string(); }

// TODO: Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(1); }

// TODO: Return the user (name) that generated this process
string Process::User() { 
    return LinuxParser::User(1); //TODO: need to pass uid here
    //return string(); 
}

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime(1); }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a[[maybe_unused]]) const { return true; }

void Process::Pid(int id){ Process::Pid_ = id; }