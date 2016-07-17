#include "bbp_parallel_profiler.h"

mila::bbp::parallel::BBPProfiler::BBPProfiler() : BBP(),
                                                  main_result_("Digits per second"),
                                                  main_duration_("Run") {
}

mila::bbp::parallel::BBPProfiler::BBPProfiler(float precision) : BBP(precision),
                                                                 main_result_("Digits per second"),
                                                                 main_duration_("Run") {
}

mila::bbp::parallel::BBPProfiler::BBPProfiler(size_t platform_id, size_t device_id) : BBP(platform_id, device_id),
                                                                                      main_result_("Digits per second"),
                                                                                      main_duration_("Run") {
}

void mila::bbp::parallel::BBPProfiler::Initialize() {
  auto start_time = std::chrono::high_resolution_clock::now();
  BBP::Initialize();
  auto end_time = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
  results_.insert(std::pair<std::string, float>("Initialize", duration));
}

std::string mila::bbp::parallel::BBPProfiler::Run(size_t number_of_digits, size_t starting_position) {
  auto start_time = std::chrono::high_resolution_clock::now();
  auto output = BBP::Run(number_of_digits, starting_position);
  auto end_time = std::chrono::high_resolution_clock::now();

  auto duration = std::chrono::duration<float>(end_time - start_time);
  auto duration_us = std::chrono::duration_cast<std::chrono::microseconds>(duration).count();
  results_.insert(std::pair<std::string, float>("Run", duration_us));
  results_.insert(std::pair<std::string, float>("Digits per second",
                                                mila::utils::GetValuePerSecond(number_of_digits, duration)));

  GetProfilingInfo();

  return output;
}

std::string mila::bbp::parallel::BBPProfiler::main_result() const {
  return main_result_;
}

std::string mila::bbp::parallel::BBPProfiler::main_duration() const {
  return main_duration_;
}

std::map<std::string, float> mila::bbp::parallel::BBPProfiler::results() const {
  return results_;
}

void mila::bbp::parallel::BBPProfiler::BuildProgram(const clpp::Program &program, const clpp::Device &device) {
  auto start_time = std::chrono::high_resolution_clock::now();
  BBP::BuildProgram(program, device);
  auto end_time = std::chrono::high_resolution_clock::now();

  auto duration = std::chrono::duration<float>(end_time - start_time);
  auto duration_us = static_cast<size_t>(std::chrono::duration_cast<std::chrono::microseconds>(duration).count());
  device_statistics_.SetBuildKernelAsMicroseconds(duration_us);
}

size_t mila::bbp::parallel::BBPProfiler::GetBuildKernelAsMicroseconds() {
  return device_statistics_.GetBuildKernelAsMicroseconds();
}

size_t mila::bbp::parallel::BBPProfiler::GetReadBufferAsMicroseconds() {
  return device_statistics_.GetReadBufferAsMicroseconds();
}

size_t mila::bbp::parallel::BBPProfiler::GetEnqueueNDRangeAsMicroseconds() {
  return device_statistics_.GetEnqueueNDRangeAsMicroseconds();
}

std::string mila::bbp::parallel::BBPProfiler::GetOpenCLStatisticsAsString() {
  return device_statistics_.GetOpenCLStatisticsAsString();
}

void mila::bbp::parallel::BBPProfiler::GetProfilingInfo() {
  if (events_.read_buffer != nullptr) {
    device_statistics_.SetReadBufferAsMicroseconds(GetProfilingInfoAsMicroseconds(events_.read_buffer));
  }
  if (events_.enqueue_nd_range != nullptr) {
    device_statistics_.SetEnqueueNDRangeAsMicroseconds(GetProfilingInfoAsMicroseconds(events_.enqueue_nd_range));
  }
}

size_t mila::bbp::parallel::BBPProfiler::GetProfilingInfoAsMicroseconds(clpp::Event event) {
  auto nanoseconds = event.getProfilingCommandEnd() - event.getProfilingCommandStart();
  auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::nanoseconds(nanoseconds));
  return static_cast<size_t>(microseconds.count());
}
