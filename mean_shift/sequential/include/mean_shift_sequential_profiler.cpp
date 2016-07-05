#include "mean_shift_sequential_profiler.h"

mila::meanshift::sequential::MeanShiftProfiler::MeanShiftProfiler() : MeanShift(),
                                                                      main_result_("Points per second"),
                                                                      main_duration_("Run"){
}

mila::meanshift::sequential::MeanShiftProfiler::MeanShiftProfiler(float precision, size_t max_iterations) : MeanShift(precision, max_iterations),
                                                                                                            main_result_("Points per second"),
                                                                                                            main_duration_("Run") {
}

std::string mila::meanshift::sequential::MeanShiftProfiler::main_duration() const {
  return main_duration_;
}

std::string mila::meanshift::sequential::MeanShiftProfiler::main_result() const {
  return main_result_;
}

std::map<std::string, float> mila::meanshift::sequential::MeanShiftProfiler::results() const {
  return results_;
}

std::vector<mila::meanshift::sequential::Point> mila::meanshift::sequential::MeanShiftProfiler::Run(const std::vector<Point> &points, float bandwidth) {
  auto start_time = std::chrono::high_resolution_clock::now();
  auto output = MeanShift::Run(points, bandwidth);
  auto end_time = std::chrono::high_resolution_clock::now();

  auto duration = std::chrono::duration<float>(end_time - start_time);
  auto duration_us = std::chrono::duration_cast<std::chrono::microseconds>(duration).count();
  results_.insert(std::pair<std::string, float>("Run", duration_us));
  results_.insert(std::pair<std::string, float>("Points per second", mila::utils::GetValuePerSecond(points.size(), duration)));

  return output;
}

mila::meanshift::sequential::MeanShiftImageProcessingProfiler::MeanShiftImageProcessingProfiler() : MeanShiftImageProcessing(),
                                                                                                    main_result_("Pixels per second"),
                                                                                                    main_duration_("RunWithImage"),
                                                                                                    number_of_points_(0) {
}

mila::meanshift::sequential::MeanShiftImageProcessingProfiler::MeanShiftImageProcessingProfiler(float precision, size_t max_iterations) : MeanShiftImageProcessing(precision, max_iterations),
                                                                                                                                          main_duration_("RunWithImage"),
                                                                                                                                          main_result_("Pixels per second"),
                                                                                                                                          number_of_points_(0) {
}

std::string mila::meanshift::sequential::MeanShiftImageProcessingProfiler::main_duration() const {
  return main_duration_;
}

std::string mila::meanshift::sequential::MeanShiftImageProcessingProfiler::main_result() const {
  return main_result_;
}

std::map<std::string, float> mila::meanshift::sequential::MeanShiftImageProcessingProfiler::results() const {
  return results_;
}

std::vector<mila::meanshift::sequential::Point> mila::meanshift::sequential::MeanShiftImageProcessingProfiler::Run(const std::vector<Point> &points, float bandwidth) {
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

void mila::meanshift::sequential::MeanShiftImageProcessingProfiler::Run(const std::string &input_file, const std::string &output_file, float bandwidth) {
  auto start_time = std::chrono::high_resolution_clock::now();
  MeanShiftImageProcessing::Run(input_file, output_file, bandwidth);
  auto end_time = std::chrono::high_resolution_clock::now();

  auto duration = std::chrono::duration<float>(end_time - start_time);
  auto duration_us = std::chrono::duration_cast<std::chrono::microseconds>(duration).count();
  auto channels_per_pixel = 4;
  results_.insert(std::pair<std::string, float>("RunWithImage", duration_us));
  results_.insert(std::pair<std::string, float>("Pixels per second", mila::utils::GetValuePerSecond(number_of_points_ / channels_per_pixel, duration)));
}
