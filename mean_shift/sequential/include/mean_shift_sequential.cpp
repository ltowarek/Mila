#include "mean_shift_sequential.h"

std::vector<mila::Point> mila::ConvertVectorToPoints(const std::vector<uint8_t> &data) {
  auto output = std::vector<Point>();

  if (data.size() % 4 != 0) {
    // TODO throw exception
    return output;
  }

  for (size_t i = 0; i < data.size(); i += 4) {
    auto point = Point();
    point.x = static_cast<float>(data[i]);
    point.y = static_cast<float>(data[i + 1]);
    point.z = static_cast<float>(data[i + 2]);
    point.w = static_cast<float>(data[i + 3]);
    output.push_back(point);
  }

  return output;
}

std::vector<uint8_t> mila::ConvertPointsToVector(const std::vector<Point> &data) {
  auto output = std::vector<uint8_t>();

  for (size_t i = 0; i < data.size(); ++i) {
    output.push_back(static_cast<uint8_t>(data[i].x));
    output.push_back(static_cast<uint8_t>(data[i].y));
    output.push_back(static_cast<uint8_t>(data[i].z));
    output.push_back(static_cast<uint8_t>(data[i].w));
  }

  return output;
}

mila::SequentialMeanShift::SequentialMeanShift() {

}

mila::SequentialMeanShift::~SequentialMeanShift() {

}

std::vector<mila::Point> mila::SequentialMeanShift::Run(const std::vector<Point> &points, const float bandwidth) {
  const auto precision = 1e-5f;
  const auto max_iterations = 100;

  auto difference_distance = 0.0f;
  auto iteration = size_t{0};

  auto shifted_points = points;
  auto still_shifting = std::vector<bool>(points.size(), true);

  do {
    difference_distance = 0.0f;
    for (size_t i = 0; i < points.size(); ++i) {
      if (!still_shifting[i]) {
        continue;
      }

      auto old_point = shifted_points[i];
      auto new_point = ShiftPoint(old_point, points, bandwidth);
      auto distance = Distance(new_point, old_point);

      if (distance > difference_distance) {
        difference_distance = distance;
      }

      if (distance < precision) {
        still_shifting[i] = false;
      }

      shifted_points[i] = new_point;
    }
    ++iteration;
  } while ((difference_distance > precision) && (iteration < max_iterations));

  return shifted_points;
}

mila::Point mila::SequentialMeanShift::ShiftPoint(const mila::Point &point,
                                                  const std::vector<mila::Point> &points,
                                                  const float bandwidth) const {
  auto shift = Point{0.0f};
  if (bandwidth != 0) {
    auto scale = 0.0f;
    for (size_t i = 0; i < points.size(); ++i) {
      auto distance = Distance(point, points[i]);
      auto weight = GaussianKernel(distance, bandwidth);
      shift.x += weight * points[i].x;
      shift.y += weight * points[i].y;
      shift.z += weight * points[i].z;
      scale += weight;
    }
    shift.x /= scale;
    shift.y /= scale;
    shift.z /= scale;
  }
  return shift;
}

float mila::SequentialMeanShift::Distance(const Point &point1, const Point &point2) const {
  return sqrtf(powf(point1.x - point2.x, 2.0f) + powf(point1.y - point2.y, 2.0f) + powf(point1.z - point2.z, 2.0f));
}

float mila::SequentialMeanShift::GaussianKernel(const float x, const float sigma) const {
  const auto pi = 3.14159265358979323846f;
  auto output = 0.0f;
  if (sigma != 0.0f) {
    output = (1.0f / (sqrtf(2.0f * pi) * sigma)) * expf(-0.5f * powf(x / sigma, 2.0f));
  }
  return output;
}

mila::SequentialMeanShiftImageProcessing::SequentialMeanShiftImageProcessing() : SequentialMeanShift() {}

std::vector<mila::Point> mila::SequentialMeanShiftImageProcessing::Run(const std::vector<Point> &points,
                                                                       float bandwidth) {
  return SequentialMeanShift::Run(points, bandwidth);
}

void mila::SequentialMeanShiftImageProcessing::Run(const std::string &input_file,
                                                   const std::string &output_file,
                                                   float bandwidth) {
  auto input_image = mila::meanshift::utils::Image(input_file);
  auto output_image = mila::meanshift::utils::Image(output_file);

  auto input_data = input_image.Read();
  auto input_points = ConvertVectorToPoints(input_data);
  auto output_points = Run(input_points, bandwidth);
  for (size_t i = 0; i < output_points.size(); ++i) {
    output_points[i].w = 255;
  }
  auto output_data = ConvertPointsToVector(output_points);

  output_image.Write(output_data, input_image.width(), input_image.height());
}
