#include "mean_shift_sequential_profiler.h"

mila::SequentialMeanShiftProfiler::SequentialMeanShiftProfiler() : SequentialMeanShift(std::shared_ptr<Logger>()),
                                                                   main_result_("Points per second"),
                                                                   main_duration_("Run") {
}

std::string mila::SequentialMeanShiftProfiler::main_duration() const {
  return main_duration_;
}

std::string mila::SequentialMeanShiftProfiler::main_result() const {
  return main_result_;
}

std::map<std::string, float> mila::SequentialMeanShiftProfiler::results() const {
  return results_;
}

std::vector<mila::Point> mila::SequentialMeanShiftProfiler::Run(const std::vector<Point> &points, float bandwidth) {
  auto start_time = std::chrono::high_resolution_clock::now();
  auto output = SequentialMeanShift::Run(points, bandwidth);
  auto end_time = std::chrono::high_resolution_clock::now();

  auto duration = std::chrono::duration<float>(end_time - start_time);
  auto duration_us = std::chrono::duration_cast<std::chrono::microseconds>(duration).count();
  results_.insert(std::pair<std::string, float>("Run", duration_us));
  results_.insert(std::pair<std::string, float>("Points per second",
                                                mila::utils::GetValuePerSecond(points.size(), duration)));

  return output;
}

mila::MeanShiftImageProcessingProfiler::MeanShiftImageProcessingProfiler(std::unique_ptr<mila::MeanShift> mean_shift,
                                                                         const std::shared_ptr<mila::Logger> logger)
    : MeanShiftImageProcessing(std::move(mean_shift), logger),
      main_result_("Pixels per second"),
      main_duration_("RunWithImage"),
      number_of_points_(0) {
}

std::string mila::MeanShiftImageProcessingProfiler::main_duration() const {
  return main_duration_;
}

std::string mila::MeanShiftImageProcessingProfiler::main_result() const {
  return main_result_;
}

std::map<std::string, float> mila::MeanShiftImageProcessingProfiler::results() const {
  return results_;
}

void mila::MeanShiftImageProcessingProfiler::Run(const std::string &input_file,
                                                 const std::string &output_file,
                                                 float bandwidth) {
  auto start_time = std::chrono::high_resolution_clock::now();
  MeanShiftImageProcessing::Run(input_file, output_file, bandwidth);
  auto end_time = std::chrono::high_resolution_clock::now();

  auto duration = std::chrono::duration<float>(end_time - start_time);
  auto duration_us = std::chrono::duration_cast<std::chrono::microseconds>(duration).count();
  auto channels_per_pixel = 4;
  results_.insert(std::pair<std::string, float>("RunWithImage", duration_us));
  results_.insert(std::pair<std::string, float>("Pixels per second",
                                                mila::utils::GetValuePerSecond(number_of_points_ / channels_per_pixel,
                                                                               duration)));
}
