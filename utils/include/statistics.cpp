#include "statistics.h"

size_t mila::statistics::OpenCLStatistics::GetBuildKernelAsMicroseconds() {
  return static_cast<size_t>(build_kernel_.count());
}

void mila::statistics::OpenCLStatistics::SetBuildKernelAsMicroseconds(size_t microseconds) {
  build_kernel_ = std::chrono::microseconds(microseconds);
}

std::string mila::statistics::OpenCLStatistics::GetBuildKernelAsString() {
  return GetStatisticsAsString("Build kernel", static_cast<size_t>(build_kernel_.count()));
}

size_t mila::statistics::OpenCLStatistics::GetReadBufferAsMicroseconds() {
  return static_cast<size_t>(read_buffer_.count());
}

void mila::statistics::OpenCLStatistics::SetReadBufferAsMicroseconds(size_t microseconds) {
  read_buffer_ = std::chrono::microseconds(microseconds);
}

std::string mila::statistics::OpenCLStatistics::GetReadBufferAsString() {
  return GetStatisticsAsString("Read buffer", static_cast<size_t>(read_buffer_.count()));
}

size_t mila::statistics::OpenCLStatistics::GetEnqueueNDRangeAsMicroseconds() {
  return static_cast<size_t>(enqueue_nd_range_.count());
}

void mila::statistics::OpenCLStatistics::SetEnqueueNDRangeAsMicroseconds(size_t microseconds) {
  enqueue_nd_range_ = std::chrono::microseconds(microseconds);
}

std::string mila::statistics::OpenCLStatistics::GetEnqueueNDRangeAsString() {
  return GetStatisticsAsString("Enqueue ND range", static_cast<size_t>(enqueue_nd_range_.count()));
}

std::string mila::statistics::OpenCLStatistics::GetOpenCLStatisticsAsString() {
  std::stringstream stream;
  stream << GetBuildKernelAsString() << ", " << GetReadBufferAsString() << ", " << GetEnqueueNDRangeAsString();
  return stream.str();
}

std::string mila::statistics::OpenCLStatistics::GetStatisticsAsString(const std::string &name, size_t value) {
  std::stringstream stream;
  stream << name << ": " << value << " us";
  return stream.str();
}
