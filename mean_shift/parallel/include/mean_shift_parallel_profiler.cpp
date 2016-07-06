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
