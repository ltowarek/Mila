#include "mean_shift_parallel_profiler.h"

mila::meanshift::parallel::MeanShiftProfiler::MeanShiftProfiler(): MeanShift(),
                                                                   main_result_("Points per second"),
                                                                   main_duration_("Run") {

}

mila::meanshift::parallel::MeanShiftProfiler::MeanShiftProfiler(size_t platform_id, size_t device_id): MeanShift(platform_id, device_id),
                                                                                                       main_result_("Points per second"),
                                                                                                       main_duration_("Run") {

}

mila::meanshift::parallel::MeanShiftProfiler::MeanShiftProfiler(size_t platform_id,
                                                                size_t device_id,
                                                                float precision,
                                                                size_t max_iterations): MeanShift(platform_id, device_id, precision, max_iterations),
                                                                                        main_result_("Points per second"),
                                                                                        main_duration_("Run") {

}

void mila::meanshift::parallel::MeanShiftProfiler::Initialize() {
  auto start_time = std::chrono::high_resolution_clock::now();
  MeanShift::Initialize();
  auto end_time = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
  results_.insert(std::pair<std::string, float>("Initialize", duration));
}

std::vector<cl_float4> mila::meanshift::parallel::MeanShiftProfiler::Run(const std::vector<cl_float4> &points,
                                                                         float bandwidth) {
  auto start_time = std::chrono::high_resolution_clock::now();
  auto output = MeanShift::Run(points, bandwidth);
  auto end_time = std::chrono::high_resolution_clock::now();

  auto duration = std::chrono::duration<float>(end_time - start_time);
  auto duration_us = std::chrono::duration_cast<std::chrono::microseconds>(duration).count();
  results_.insert(std::pair<std::string, float>("Run", duration_us));
  results_.insert(std::pair<std::string, float>("Points per second", mila::utils::GetValuePerSecond(points.size(), duration)));

  GetProfilingInfo();

  return output;
}

void mila::meanshift::parallel::MeanShiftProfiler::BuildProgram(const clpp::Program &program, const clpp::Device &device) {
  auto start_time = std::chrono::high_resolution_clock::now();
  MeanShift::BuildProgram(program, device);
  auto end_time = std::chrono::high_resolution_clock::now();

  auto duration = std::chrono::duration<float>(end_time - start_time);
  auto duration_us = static_cast<size_t>(std::chrono::duration_cast<std::chrono::microseconds>(duration).count());
  device_statistics_.SetBuildKernelAsMicroseconds(duration_us);
}

size_t mila::meanshift::parallel::MeanShiftProfiler::GetBuildKernelAsMicroseconds() {
  return device_statistics_.GetBuildKernelAsMicroseconds();
}

size_t mila::meanshift::parallel::MeanShiftProfiler::GetCopyBufferAsMicroseconds() {
  return device_statistics_.GetCopyBufferAsMicroseconds();
}

size_t mila::meanshift::parallel::MeanShiftProfiler::GetReadBufferAsMicroseconds() {
  return device_statistics_.GetReadBufferAsMicroseconds();
}

size_t mila::meanshift::parallel::MeanShiftProfiler::GetEnqueueNDRangeAsMicroseconds() {
  return device_statistics_.GetEnqueueNDRangeAsMicroseconds();
}

std::string mila::meanshift::parallel::MeanShiftProfiler::GetOpenCLStatisticsAsString() {
  return device_statistics_.GetOpenCLStatisticsAsString();
}

void mila::meanshift::parallel::MeanShiftProfiler::GetProfilingInfo() {
  if (!events_.copy_buffer.empty()) {
    device_statistics_.SetCopyBufferAsMicroseconds(mila::utils::Sum(GetProfilingInfoAsMicroseconds(events_.copy_buffer)));
  }
  if (!events_.read_buffer_with_distances.empty()) {
    device_statistics_.SetReadBufferAsMicroseconds(mila::utils::Sum(GetProfilingInfoAsMicroseconds(events_.read_buffer_with_distances)));
  }
  if (!events_.enqueue_nd_range.empty()) {
    device_statistics_.SetEnqueueNDRangeAsMicroseconds(mila::utils::Sum(GetProfilingInfoAsMicroseconds(events_.enqueue_nd_range)));
  }
}

size_t mila::meanshift::parallel::MeanShiftProfiler::GetProfilingInfoAsMicroseconds(clpp::Event event) {
  auto nanoseconds = event.getProfilingCommandEnd() - event.getProfilingCommandStart();
  auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::nanoseconds(nanoseconds));
  return static_cast<size_t>(microseconds.count());
}

std::vector<size_t> mila::meanshift::parallel::MeanShiftProfiler::GetProfilingInfoAsMicroseconds(const std::vector<clpp::Event>& events) {
  auto output = std::vector<size_t>();
  for (int i = 0; i < events.size(); ++i) {
    output.push_back(GetProfilingInfoAsMicroseconds(events[i]));
  }
  return output;
}

std::string mila::meanshift::parallel::MeanShiftProfiler::main_result() const {
  return main_result_;
}

std::string mila::meanshift::parallel::MeanShiftProfiler::main_duration() const {
  return main_duration_;
}

std::map<std::string, float> mila::meanshift::parallel::MeanShiftProfiler::results() const {
  return results_;
}

mila::meanshift::parallel::MeanShiftImageProcessingProfiler::MeanShiftImageProcessingProfiler(): MeanShiftImageProcessing(),
                                                                                                 main_result_("Pixels per second"),
                                                                                                 main_duration_("RunWithImage") {

}

mila::meanshift::parallel::MeanShiftImageProcessingProfiler::MeanShiftImageProcessingProfiler(size_t platform_id,
                                                                                              size_t device_id): MeanShiftImageProcessing(platform_id, device_id),
                                                                                                                 main_result_("Pixels per second"),
                                                                                                                 main_duration_("RunWithImage") {

}

mila::meanshift::parallel::MeanShiftImageProcessingProfiler::MeanShiftImageProcessingProfiler(size_t platform_id,
                                                                                              size_t device_id,
                                                                                              float precision,
                                                                                              size_t max_iterations): MeanShiftImageProcessing(platform_id, device_id, precision, max_iterations),
                                                                                                                      main_result_("Pixels per second"),
                                                                                                                      main_duration_("RunWithImage") {

}

void mila::meanshift::parallel::MeanShiftImageProcessingProfiler::Initialize() {
  auto start_time = std::chrono::high_resolution_clock::now();
  MeanShiftImageProcessing::Initialize();
  auto end_time = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
  results_.insert(std::pair<std::string, float>("Initialize", duration));
}

std::vector<cl_float4> mila::meanshift::parallel::MeanShiftImageProcessingProfiler::Run(const std::vector<cl_float4> &points,
                                                                                        float bandwidth) {
  auto start_time = std::chrono::high_resolution_clock::now();
  auto output = MeanShiftImageProcessing::Run(points, bandwidth);
  auto end_time = std::chrono::high_resolution_clock::now();

  auto duration = std::chrono::duration<float>(end_time - start_time);
  auto duration_us = std::chrono::duration_cast<std::chrono::microseconds>(duration).count();
  results_.insert(std::pair<std::string, float>("RunWithoutImage", duration_us));
  results_.insert(std::pair<std::string, float>("Points per second", mila::utils::GetValuePerSecond(points.size(), duration)));

  number_of_points_ = points.size();

  return output;
}

void mila::meanshift::parallel::MeanShiftImageProcessingProfiler::Run(const std::string &input_file,
                                                                      const std::string &output_file,
                                                                      float bandwidth) {
  auto start_time = std::chrono::high_resolution_clock::now();
  MeanShiftImageProcessing::Run(input_file, output_file, bandwidth);
  auto end_time = std::chrono::high_resolution_clock::now();

  auto duration = std::chrono::duration<float>(end_time - start_time);
  auto duration_us = std::chrono::duration_cast<std::chrono::microseconds>(duration).count();
  auto channels_per_pixel = 4;
  results_.insert(std::pair<std::string, float>("RunWithImage", duration_us));
  results_.insert(std::pair<std::string, float>("Pixels per second", mila::utils::GetValuePerSecond(number_of_points_ / channels_per_pixel, duration)));

  GetProfilingInfo();
}

void mila::meanshift::parallel::MeanShiftImageProcessingProfiler::BuildProgram(const clpp::Program &program, const clpp::Device &device) {
  auto start_time = std::chrono::high_resolution_clock::now();
  MeanShift::BuildProgram(program, device);
  auto end_time = std::chrono::high_resolution_clock::now();

  auto duration = std::chrono::duration<float>(end_time - start_time);
  auto duration_us = static_cast<size_t>(std::chrono::duration_cast<std::chrono::microseconds>(duration).count());
  device_statistics_.SetBuildKernelAsMicroseconds(duration_us);
}

size_t mila::meanshift::parallel::MeanShiftImageProcessingProfiler::GetBuildKernelAsMicroseconds() {
  return device_statistics_.GetBuildKernelAsMicroseconds();
}

size_t mila::meanshift::parallel::MeanShiftImageProcessingProfiler::GetCopyBufferAsMicroseconds() {
  return device_statistics_.GetCopyBufferAsMicroseconds();
}

size_t mila::meanshift::parallel::MeanShiftImageProcessingProfiler::GetReadBufferAsMicroseconds() {
  return device_statistics_.GetReadBufferAsMicroseconds();
}

size_t mila::meanshift::parallel::MeanShiftImageProcessingProfiler::GetEnqueueNDRangeAsMicroseconds() {
  return device_statistics_.GetEnqueueNDRangeAsMicroseconds();
}

std::string mila::meanshift::parallel::MeanShiftImageProcessingProfiler::GetOpenCLStatisticsAsString() {
  return device_statistics_.GetOpenCLStatisticsAsString();
}

void mila::meanshift::parallel::MeanShiftImageProcessingProfiler::GetProfilingInfo() {
  if (!events_.copy_buffer.empty()) {
    device_statistics_.SetCopyBufferAsMicroseconds(mila::utils::Sum(GetProfilingInfoAsMicroseconds(events_.copy_buffer)));
  }
  if (!events_.read_buffer_with_distances.empty()) {
    device_statistics_.SetReadBufferAsMicroseconds(mila::utils::Sum(GetProfilingInfoAsMicroseconds(events_.read_buffer_with_distances)));
  }
  if (!events_.enqueue_nd_range.empty()) {
    device_statistics_.SetEnqueueNDRangeAsMicroseconds(mila::utils::Sum(GetProfilingInfoAsMicroseconds(events_.enqueue_nd_range)));
  }
}

size_t mila::meanshift::parallel::MeanShiftImageProcessingProfiler::GetProfilingInfoAsMicroseconds(clpp::Event event) {
  auto nanoseconds = event.getProfilingCommandEnd() - event.getProfilingCommandStart();
  auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::nanoseconds(nanoseconds));
  return static_cast<size_t>(microseconds.count());
}

std::vector<size_t> mila::meanshift::parallel::MeanShiftImageProcessingProfiler::GetProfilingInfoAsMicroseconds(const std::vector<clpp::Event>& events) {
  auto output = std::vector<size_t>();
  for (int i = 0; i < events.size(); ++i) {
    output.push_back(GetProfilingInfoAsMicroseconds(events[i]));
  }
  return output;
}

std::string mila::meanshift::parallel::MeanShiftImageProcessingProfiler::main_result() const {
  return main_result_;
}

std::string mila::meanshift::parallel::MeanShiftImageProcessingProfiler::main_duration() const {
  return main_duration_;
}

std::map<std::string, float> mila::meanshift::parallel::MeanShiftImageProcessingProfiler::results() const {
  return results_;
}
