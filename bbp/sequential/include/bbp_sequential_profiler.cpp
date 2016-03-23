#include "bbp_sequential_profiler.h"

mila::bbp::sequential::BBPProfiler::BBPProfiler() : BBP(), main_result_("Run") {
}

mila::bbp::sequential::BBPProfiler::BBPProfiler(float precision) : BBP(precision), main_result_("Run") {
}

std::string mila::bbp::sequential::BBPProfiler::main_result() const {
  return main_result_;
}

std::map<std::string, int64_t> mila::bbp::sequential::BBPProfiler::results() const {
  return results_;
}

std::string mila::bbp::sequential::BBPProfiler::Run(size_t number_of_digits, size_t starting_position) {
  auto start_time = std::chrono::high_resolution_clock::now();
  auto output = BBP::Run(number_of_digits, starting_position);
  auto end_time = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
  results_.insert(std::pair<std::string, int64_t>("Run", duration));
  return output;
}
