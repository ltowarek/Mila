#include "mean_shift_image_processing.h"

mila::MeanShiftImageProcessing::MeanShiftImageProcessing(std::unique_ptr<mila::MeanShift> mean_shift,
                                                         const std::shared_ptr<mila::Logger> logger) :
    logger_(logger), mean_shift_(std::move(mean_shift)) {

}
void mila::MeanShiftImageProcessing::Run(const std::string &input_file,
                                         const std::string &output_file,
                                         const float bandwidth) {
  auto input_image = mila::Image(input_file);
  auto output_image = mila::Image(output_file);

  auto input_data = input_image.Read();
  const auto input_points = ConvertVectorToPoints(input_data);
  auto output_points = mean_shift_->Run(input_points, bandwidth);
  for (size_t i = 0; i < output_points.size(); ++i) {
    output_points[i].w = 255;
  }
  const auto output_data = ConvertPointsToVector(output_points);

  output_image.Write(output_data, input_image.width(), input_image.height());
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
                                                 const float bandwidth) {
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
