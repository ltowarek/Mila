#ifndef MILA_BBP_PARALLEL_PROFILER_H_
#define MILA_BBP_PARALLEL_PROFILER_H_

#include <chrono>
#include <map>
#include "bbp_parallel.h"

namespace mila {
namespace bbp {
namespace parallel {

class OpenCLStatistics {
 public:
  inline size_t GetBuildKernelAsMicroseconds() {
    return static_cast<size_t>(build_kernel_.count());
  }

  inline void SetBuildKernelAsMicroseconds(size_t microseconds) {
    build_kernel_ = std::chrono::microseconds(microseconds);
  }

  inline std::string GetBuildKernelAsString() {
    return GetStatisticsAsString("Build kernel", static_cast<size_t>(build_kernel_.count()));
  }

  inline size_t GetReadBufferAsMicroseconds() {
    return static_cast<size_t>(read_buffer_.count());
  }

  inline void SetReadBufferAsMicroseconds(size_t microseconds) {
    read_buffer_ = std::chrono::microseconds(microseconds);
  }

  inline std::string GetReadBufferAsString() {
    return GetStatisticsAsString("Read buffer", static_cast<size_t>(read_buffer_.count()));
  }

  inline size_t GetEnqueueNDRangeAsMicroseconds() {
    return static_cast<size_t>(enqueue_nd_range_.count());
  }

  inline void SetEnqueueNDRangeAsMicroseconds(size_t microseconds) {
    enqueue_nd_range_ = std::chrono::microseconds(microseconds);
  }

  inline std::string GetEnqueueNDRangeAsString() {
    return GetStatisticsAsString("Enqueue ND range", static_cast<size_t>(enqueue_nd_range_.count()));
  }

  inline std::string GetOpenCLStatisticsAsString() {
    std::stringstream stream;
    stream << GetBuildKernelAsString() << ", " << GetReadBufferAsString() << ", " << GetEnqueueNDRangeAsString();
    return stream.str();
  }
 private:
  inline std::string GetStatisticsAsString(const std::string& name, size_t value) {
    std::stringstream stream;
    stream << name << ": " << value << " us";
    return stream.str();
  }

  std::chrono::microseconds build_kernel_ = std::chrono::microseconds(0);
  std::chrono::microseconds enqueue_nd_range_ = std::chrono::microseconds(0);
  std::chrono::microseconds read_buffer_ = std::chrono::microseconds(0);
};

class BBPProfiler : public BBP {
 public:
  BBPProfiler();
  BBPProfiler(float precision);
  BBPProfiler(size_t platform_id, size_t device_id);

  void Initialize() override;
  std::string Run(size_t number_of_digits, size_t starting_position) override;
  size_t GetBuildKernelAsMicroseconds();
  size_t GetReadBufferAsMicroseconds();
  size_t GetEnqueueNDRangeAsMicroseconds();
  std::string GetOpenCLStatisticsAsString();

  std::string main_result() const;
  std::string main_duration() const;
  std::map<std::string, float> results() const;
 private:
  void BuildProgram(const clpp::Program& program, const clpp::Device& device) override;
  void GetProfilingInfo();
  size_t GetProfilingInfoAsMicroseconds(clpp::Event);

  const std::string main_result_;
  const std::string main_duration_;
  std::map<std::string, float> results_;
  OpenCLStatistics device_statistics_;
};
};  // parallel
};  // bbp
}  // mila

#endif  // MILA_BBP_PARALLEL_PROFILER_H_
