#include "mean_shift_sequential.h"

float mila::meanshift::sequential::Distance(const Point &point1, const Point &point2) {
  return sqrtf(powf(point1.x - point2.x, 2.0f) + powf(point1.y - point2.y, 2.0f) + powf(point1.z - point2.z, 2.0f));
}

float mila::meanshift::sequential::GaussianKernel(float x, float sigma) {
  auto output = 0.0f;
  if (sigma != 0) {
    output = (1.0f / (sqrtf(2.0f * pi) * sigma)) * expf(-0.5f * powf(x / sigma, 2.0f));
  }
  return output;
}

std::vector<mila::meanshift::sequential::Point> mila::meanshift::sequential::ConvertVectorToPoints(const std::vector<uint8_t> &data) {
  auto output = std::vector<Point>();

  if (data.size() % 4 != 0) {
    // TODO throw exception
    return output;
  }

  for (size_t i = 0; i < data.size(); i+=4) {
    auto point = Point();
    point.x = static_cast<float>(data[i]);
    point.y = static_cast<float>(data[i+1]);
    point.z = static_cast<float>(data[i+2]);
    point.w = static_cast<float>(data[i+3]);
    output.push_back(point);
  }

  return output;
}

std::vector<uint8_t> mila::meanshift::sequential::ConvertPointsToVector(const std::vector<Point> &data) {
  auto output = std::vector<uint8_t>();

  for (size_t i = 0; i < data.size(); ++i) {
    output.push_back(static_cast<uint8_t>(data[i].x));
    output.push_back(static_cast<uint8_t>(data[i].y));
    output.push_back(static_cast<uint8_t>(data[i].z));
    output.push_back(static_cast<uint8_t>(data[i].w));
  }

  return output;
}

mila::meanshift::sequential::MeanShift::MeanShift() : MeanShift(1e-5, 100) {}

mila::meanshift::sequential::MeanShift::MeanShift(float precision, size_t max_iterations) : precision_(precision), max_iterations_(max_iterations) {}

mila::meanshift::sequential::Point mila::meanshift::sequential::MeanShift::ShiftPoint(const mila::meanshift::sequential::Point &point,
                                                                                      const std::vector<mila::meanshift::sequential::Point> &points,
                                                                                      float bandwidth) const {
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

float mila::meanshift::sequential::MeanShift::precision() const {
  return precision_;
}

size_t mila::meanshift::sequential::MeanShift::max_iterations() const {
  return max_iterations_;
}

std::vector<mila::meanshift::sequential::Point> mila::meanshift::sequential::MeanShift::Run(const std::vector<Point> &points, float bandwidth) const {
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

      if (distance < precision_) {
        still_shifting[i] = false;
      }

      shifted_points[i] = new_point;
    }
    ++iteration;
  } while ((difference_distance > precision_) && (iteration < max_iterations_));

  return shifted_points;
}
