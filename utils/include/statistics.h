#ifndef MILA_STATISTICS_H_
#define MILA_STATISTICS_H_

#include <string>
#include <sstream>
#include <chrono>

namespace mila {
namespace statistics {

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

};  // statistics
}  // mila

#endif  //MILA_STATISTICS_H_
