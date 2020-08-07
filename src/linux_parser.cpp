#include <dirent.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
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

// DONE: An example of how to read data from the filesystem
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

// BONUS: Update this to use std::filesystem
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

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() {
  float memoryUtil;
  string line;  // to parse the lines
  string attribute;
  long int memtotal, memfree;
  std::ifstream filestream(kProcDirectory + kMeminfoFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {  // retrieve the line
      std::istringstream linestream(
          line);                // create a stream to process the line
      linestream >> attribute;  // extract attribute name (until space)
      if (attribute == "MemTotal:") {
        linestream >> memtotal;
      } else if (attribute == "MemFree:") {
        linestream >> memfree;
        break;
      }
    }
    // std::cout << memtotal <<"  "<< memfree << "\n";
    // std::cout << attribute << " \n" << attribval << "\n";

    // while(std::getline(filestream, line)){
    //   //replace : with " "
    // }
  }
  // memoryUtil = ((memtotal - memfree)) / memtotal;
  // doing above will result in zero as float typecast happens later
  // can static cast numerator in above expression or do as below (first step
  // implicit cast)
  memoryUtil = (memtotal - memfree);
  memoryUtil = memoryUtil / memtotal;
  return memoryUtil;
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() {
  // /proc/uptime
  long uptime;
  string line;
  std::ifstream filestream(kProcDirectory + kUptimeFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    linestream >> uptime;
  }
  // std::cout << uptime << "test \n";
  return uptime;
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { return {}; }

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() {
  // /proc/stat
  string line;
  string attribute;
  int processes;
  // access the stream
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    // loop through the lines
    while (std::getline(filestream, line)) {
      // get the line and pass it to the stream
      std::istringstream linestream(line);
      linestream >> attribute;
      // std::cout << "attribute";
      // std::cout << "\n";
      // check the value of the first element
      if (attribute == "processes") {
        // extract when value is equal to 'processes' and break loop
        linestream >> processes;
        break;
      }
    }
  }
  return processes;  // 0;
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() {
  // again /proc/stat
  string line;
  string attribute;
  int procsrunning;
  // access the file
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    // iterate through the lines in the file
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      linestream >> attribute;
      if (attribute == "procs_running") {
        linestream >> procsrunning;
        break;
      }
    }
  }
  return procsrunning;  // 0;
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) { return string(); }

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) { 
  string line;
  string attribute;
  long Ram;
  // need to extract from proc/pid/status
  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatusFilename);
  if(filestream.is_open()){
    while(std::getline(filestream, line)){
      std::istringstream linestream(line);
      linestream >> attribute;
      if(attribute == "VmSize:"){
        linestream >> Ram;
      }
    }
  }
  Ram = Ram / 1024; // convert to MB
  return to_string(Ram); 
}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) { 
  string line;
  string attribute;
  string uid;

  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatusFilename);
  if(filestream.is_open()){
    
    while(std::getline(filestream, line)){
      std::istringstream linestream(line);
      linestream >> attribute;
      if(attribute == "Uid:"){
        linestream >> uid;
        break;
      }
    }
  }
//   std::cout << uid << " test\n";
  return uid; 
} 

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) { 
  // need to match uid to username here
  // name:password:UID:GID:GECOS:directory:shell
  // parse each line and compare uid to the uid from the uid function
  // when it matches we pass the string

  string uidr = LinuxParser::Uid(pid);
  std::ifstream filestream(kPasswordPath);
  string line;
  string name, pwd, uid;
  
  if(filestream.is_open()){
  	while(std::getline(filestream, line)){
     
      // will need to first replace the ':' with space so can stream one 
      // after the other
      std::replace(line.begin(), line.end(), ':', ' ');
      // then pass the line to linestream
      std::istringstream linestream(line);
      linestream >> name >> pwd >> uid;
      //std::cout << uid << "\n";
      if(uidr == uid){
        //std::cout << name << "\n";
        break;
      }
    }
  }
  return name; 
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) { 
  // can be retrieved from the command /proc/[pid]/stat
  // item 22 is the starttime
  // measured in clock ticks, need to convert to seconds
  // divide the "clock ticks" value by sysconf(_SC_CLK_TCK)
  string line;
  string attribute;
  long uptime;
  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatFilename);
  if(filestream.is_open()){
    std::getline(filestream, line);
    std::istringstream linestream(line);
    // item 22 is the starttime
    for(auto i = 0; i < 22; i++)
      linestream >> attribute;
    
    uptime = std::stol(attribute);
    
    // convert ticks to seconds
    uptime = uptime/ (sysconf(_SC_CLK_TCK));
    //std::cout << uptime << "ss \n";
  }
  
  return uptime; 
}