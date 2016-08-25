#include "bbp_sequential_profiler.h"
#include "utils.h"

mila::SequentialBBPProfiler::SequentialBBPProfiler(const std::shared_ptr<Logger> logger) : SequentialBBP(logger),
                                                                                           main_result_("Digits per second"),
                                                                                           main_duration_("Run") {
}

std::string mila::SequentialBBPProfiler::main_result() const {
  return main_result_;
}

std::string mila::SequentialBBPProfiler::main_duration() const {
  return main_duration_;
}

std::map<std::string, float> mila::SequentialBBPProfiler::results() const {
  return results_;
}

std::vector<float> mila::SequentialBBPProfiler::ComputeDigits(size_t number_of_digits, size_t starting_position) {
  auto start_time = std::chrono::high_resolution_clock::now();
  auto output = SequentialBBP::ComputeDigits(number_of_digits, starting_position);
  auto end_time = std::chrono::high_resolution_clock::now();

  auto duration = std::chrono::duration<float>(end_time - start_time);
  auto duration_us = std::chrono::duration_cast<std::chrono::microseconds>(duration).count();
  results_.insert(std::pair<std::string, float>("Run", duration_us));
  results_.insert(std::pair<std::string, float>("Digits per second",
                                                mila::utils::GetValuePerSecond(number_of_digits, duration)));

  return output;
}
mila::SequentialBBPProfiler::~SequentialBBPProfiler() {

}

