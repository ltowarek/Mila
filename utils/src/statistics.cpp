#include "statistics.hpp"

void mila::PrintResultStatistics(const std::string &name,
                                 const std::string &unit,
                                 const std::vector<float> &result,
                                 const mila::Logger &logger) {
  logger.Info("%s mean: %f %s", name.c_str(), mila::Mean(result), unit.c_str());
  logger.Info("%s median: %f %s", name.c_str(), mila::Median(result), unit.c_str());
  logger.Info("%s standard deviation: %f %s", name.c_str(), mila::StandardDeviation(result), unit.c_str());
  logger.Info("%s coefficient of variation: %f", name.c_str(), mila::CoefficientOfVariation(result), unit.c_str());
}
size_t mila::OpenCLStatistics::GetBuildKernelAsMicroseconds() {
  return static_cast<size_t>(build_kernel_.count());
}

void mila::OpenCLStatistics::SetBuildKernelAsMicroseconds(size_t microseconds) {
  build_kernel_ = std::chrono::microseconds(microseconds);
}

std::string mila::OpenCLStatistics::GetBuildKernelAsString() {
  return GetStatisticsAsString("Build kernel", static_cast<size_t>(build_kernel_.count()));
}

size_t mila::OpenCLStatistics::GetCopyBufferAsMicroseconds() {
  return static_cast<size_t>(copy_buffer_.count());
}

void mila::OpenCLStatistics::SetCopyBufferAsMicroseconds(size_t microseconds) {
  copy_buffer_ = std::chrono::microseconds(microseconds);
}

std::string mila::OpenCLStatistics::GetCopyBufferAsString() {
  return GetStatisticsAsString("Copy buffer", static_cast<size_t>(copy_buffer_.count()));
}

size_t mila::OpenCLStatistics::GetReadBufferAsMicroseconds() {
  return static_cast<size_t>(read_buffer_.count());
}

void mila::OpenCLStatistics::SetReadBufferAsMicroseconds(size_t microseconds) {
  read_buffer_ = std::chrono::microseconds(microseconds);
}

std::string mila::OpenCLStatistics::GetReadBufferAsString() {
  return GetStatisticsAsString("Read buffer", static_cast<size_t>(read_buffer_.count()));
}

size_t mila::OpenCLStatistics::GetEnqueueNDRangeAsMicroseconds() {
  return static_cast<size_t>(enqueue_nd_range_.count());
}

void mila::OpenCLStatistics::SetEnqueueNDRangeAsMicroseconds(size_t microseconds) {
  enqueue_nd_range_ = std::chrono::microseconds(microseconds);
}

std::string mila::OpenCLStatistics::GetEnqueueNDRangeAsString() {
  return GetStatisticsAsString("Enqueue ND range", static_cast<size_t>(enqueue_nd_range_.count()));
}

std::string mila::OpenCLStatistics::GetOpenCLStatisticsAsString() {
  std::stringstream stream;
  if (build_kernel_.count() > 0) {
    stream << GetBuildKernelAsString() << ", ";
  }
  if (copy_buffer_.count() > 0) {
    stream << GetCopyBufferAsString() << ", ";
  }
  if (read_buffer_.count() > 0) {
    stream << GetReadBufferAsString() << ", ";
  }
  if (enqueue_nd_range_.count() > 0) {
    stream << GetEnqueueNDRangeAsString();
  }
  return stream.str();
}

std::string mila::OpenCLStatistics::GetStatisticsAsString(const std::string &name, size_t value) {
  std::stringstream stream;
  stream << name << ": " << value << " us";
  return stream.str();
}
