#include "bbp_sequential_profiler.h"

mila::bbp::sequential::BBPProfiler::BBPProfiler() : BBP(),
                                                    main_result_("Digits per second"),
                                                    main_duration_("Run") {
}

mila::bbp::sequential::BBPProfiler::BBPProfiler(float precision) : BBP(precision),
                                                                   main_result_("Digits per second"),
                                                                   main_duration_("Run") {
}

std::string mila::bbp::sequential::BBPProfiler::main_result() const {
  return main_result_;
}

std::string mila::bbp::sequential::BBPProfiler::main_duration() const {
  return main_duration_;
}

std::map<std::string, float> mila::bbp::sequential::BBPProfiler::results() const {
  return results_;
}

std::string mila::bbp::sequential::BBPProfiler::Run(size_t number_of_digits, size_t starting_position) {
  auto start_time = std::chrono::high_resolution_clock::now();
  auto output = BBP::Run(number_of_digits, starting_position);
  auto end_time = std::chrono::high_resolution_clock::now();

  auto duration = std::chrono::duration<float>(end_time - start_time);
  auto duration_us = std::chrono::duration_cast<std::chrono::microseconds>(duration).count();
  results_.insert(std::pair<std::string, float>("Run", duration_us));
  results_.insert(std::pair<std::string, float>("Digits per second", GetDigitsPerSecond(number_of_digits, duration)));

  return output;
}

float mila::bbp::sequential::BBPProfiler::GetDigitsPerSecond(size_t number_of_digits, std::chrono::duration<float> duration) {
  auto digits_per_second = (duration.count() > 0.0f) ? static_cast<float>(number_of_digits) / duration.count() : 0.0f;
  return digits_per_second;
}
