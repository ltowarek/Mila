#include "mean_shift_sequential.hpp"

mila::SequentialMeanShift::SequentialMeanShift(const std::shared_ptr<mila::Logger> logger) : logger_(logger) {

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

