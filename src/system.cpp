#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "linux_parser.h"
#include "process.h"
#include "processor.h"
#include "system.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;
// using LinuxParser;

System::System()
    : OperatingSystem_(LinuxParser::OperatingSystem()),
      Kernel_(LinuxParser::Kernel()) {}

// TODO: Return the system's CPU
Processor& System::Cpu() { return cpu_; }

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() {
  // need to iterate through the processes from the parser and populate the
  // vector with process objects only populate the ids now not required to
  // populate all data now , can be done when displaying
  vector<int> Pids = LinuxParser::Pids();
  processes_.clear();
  // this is required to create a new set of vector entries everytime,
  // else will run out of memory;
  for (int pid : Pids) {  // range based for loop
    Process proc;
    proc.Pid(pid);
    processes_.emplace_back(proc);
  }
  // sort the processes based on memory usage
  std::sort(processes_.begin(), processes_.end());
  return processes_;
}

// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() { return System::Kernel_; }

// TODO: Return the system's memory utilization
float System::MemoryUtilization() { return LinuxParser::MemoryUtilization(); }

// TODO: Return the operating system name
std::string System::OperatingSystem() { return System::OperatingSystem_; }

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() { return LinuxParser::RunningProcesses(); }

// TODO: Return the total number of processes on the system
int System::TotalProcesses() { return LinuxParser::TotalProcesses(); }

// TODO: Return the number of seconds since the system started running
long int System::UpTime() { return LinuxParser::UpTime(); }