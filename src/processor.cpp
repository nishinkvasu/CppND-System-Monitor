#include "processor.h"
#include "linux_parser.h"
#include "string"
#include "vector"

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {
  std::vector<std::string> CpuUsage = LinuxParser::CpuUtilization();
  int i = 0;
  long totalidle = 0;
  long totalnonidle = 0;

  // user nice system idle iowait irq softirq steal guest guest_nice
  //  0    1    2     3     4    5     6      7     8     9
  // idle = 3 + 4
  // nonidle = 0 + 1 + 2 + 5 + 6 + 7
  for (auto x : CpuUsage) {
    if ((i == 3) || (i == 4)) {
      totalidle += std::stol(x);
    } else {
      totalnonidle += std::stol(x);
    }
    i++;
  }

  auto total = totalnonidle + totalidle;
  auto prevtotal = Processor::prevtotalnonidle + Processor::prevtotalidle;

  auto totald = total - prevtotal;
  auto idled = totalidle - Processor::prevtotalidle;

  float util = (totald - idled);
  util = util / totald;

  Processor::prevtotalidle = totalidle;
  Processor::prevtotalnonidle = totalnonidle;

  return util;
}