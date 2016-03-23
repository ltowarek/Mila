#include "bbp_parallel_profiler.h"

mila::bbp::parallel::BBPProfiler::BBPProfiler() : BBP(), main_result_("Run") {
}

mila::bbp::parallel::BBPProfiler::BBPProfiler(float precision) : BBP(precision), main_result_("Run") {
}

mila::bbp::parallel::BBPProfiler::BBPProfiler(size_t platform_id, size_t device_id) : BBP(platform_id, device_id), main_result_("Run") {
}

void mila::bbp::parallel::BBPProfiler::Initialize() {
  auto start_time = std::chrono::high_resolution_clock::now();
  BBP::Initialize();
  auto end_time = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
  results_.insert(std::pair<std::string, int64_t>("Initialize", duration));
}

std::string mila::bbp::parallel::BBPProfiler::Run(size_t number_of_digits, size_t starting_position) {
  auto start_time = std::chrono::high_resolution_clock::now();
  auto output = BBP::Run(number_of_digits, starting_position);
  auto end_time = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
  results_.insert(std::pair<std::string, int64_t>("Run", duration));
  return output;
}

std::string mila::bbp::parallel::BBPProfiler::main_result() const {
  return main_result_;
}

std::map<std::string, int64_t> mila::bbp::parallel::BBPProfiler::results() const {
  return results_;
}
