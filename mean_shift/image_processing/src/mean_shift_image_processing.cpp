#include "mean_shift_image_processing.hpp"

mila::GenericMeanShiftImageProcessing::GenericMeanShiftImageProcessing(std::unique_ptr<mila::MeanShift> mean_shift,
                                                                       const std::shared_ptr<mila::Logger> logger) :
    logger_(logger), mean_shift_(std::move(mean_shift)) {

}

void mila::GenericMeanShiftImageProcessing::Run(const std::string &input_file,
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
