#include <string>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) {
  int hours, minutes, secs;
  char times[9];
  hours = seconds / 3600;
  minutes = (seconds % 3600) / 60;
  secs = (seconds % 3600) - (minutes * 60);
  snprintf(times, 9, "%02d:%02d:%02d", hours, minutes, secs);
  string time(times);  // = std::to_string(hours) +":"+std::to_string(minutes)
                       // +":"+ std::to_string(secs);
  return time;
}