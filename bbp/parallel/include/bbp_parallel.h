#ifndef MILA_BBP_PARALLEL_H_
#define MILA_BBP_PARALLEL_H_

#include <cstdio>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "clpp.h"

#include "bbp_utils.h"
#include "utils.h"

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

class BBP {
 public:
  BBP();
  BBP(float precision);
  BBP(size_t platform_id, size_t device_id);
  ~BBP();

  virtual void Initialize();
  virtual std::string Run(size_t number_of_digits, size_t starting_position);
  std::vector<float> ComputeDigits(size_t number_of_digits, int starting_position);

  float precision() const;
  size_t platform_id() const;
  size_t device_id() const;
  clpp::Platform platform() const;
  clpp::Device device() const;
  clpp::Context context() const;
  clpp::Queue queue() const;
  clpp::Kernel kernel() const;
 protected:
  virtual void BuildProgram(const clpp::Program& program, const clpp::Device& device);

  struct Events {
    clpp::Event read_buffer;
    clpp::Event enqueue_nd_range;
  };

  Events events_;
  const float precision_;
  size_t platform_id_;
  size_t device_id_;
  clpp::Platform platform_;
  clpp::Device device_;
  clpp::Context context_;
  clpp::Queue queue_;
  clpp::Kernel kernel_;
};
};  // parallel
};  // bbp
}  // mila

#endif  // MILA_BBP_PARALLEL_H_
