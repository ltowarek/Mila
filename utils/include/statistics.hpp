#ifndef MILA_STATISTICS_H
#define MILA_STATISTICS_H

#include <string>
#include <sstream>
#include <chrono>
#include <vector>

#include "utils.hpp"
#include "logger.hpp"

namespace mila {
void PrintResultStatistics(const std::string &name,
                           const std::string &unit,
                           const std::vector<float> &result,
                           const mila::Logger &logger);
class OpenCLStatistics {
 public:
   size_t GetBuildKernelAsMicroseconds();
   void SetBuildKernelAsMicroseconds(size_t microseconds);
   std::string GetBuildKernelAsString();

   size_t GetCopyBufferAsMicroseconds();
   void SetCopyBufferAsMicroseconds(size_t microseconds);
   std::string GetCopyBufferAsString();

   size_t GetReadBufferAsMicroseconds();
   void SetReadBufferAsMicroseconds(size_t microseconds);
   std::string GetReadBufferAsString();

   size_t GetEnqueueNDRangeAsMicroseconds();
   void SetEnqueueNDRangeAsMicroseconds(size_t microseconds);
   std::string GetEnqueueNDRangeAsString();

   std::string GetOpenCLStatisticsAsString();

 private:
   std::string GetStatisticsAsString(const std::string &name, size_t value);

  std::chrono::microseconds build_kernel_ = std::chrono::microseconds(0);
  std::chrono::microseconds enqueue_nd_range_ = std::chrono::microseconds(0);
  std::chrono::microseconds copy_buffer_ = std::chrono::microseconds(0);
  std::chrono::microseconds read_buffer_ = std::chrono::microseconds(0);
};
}  // mila
#endif  //MILA_STATISTICS_H
