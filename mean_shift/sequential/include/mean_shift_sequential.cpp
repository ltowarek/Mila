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

mila::meanshift::sequential::Point mila::meanshift::sequential::MeanShift::ShiftPoint(const mila::meanshift::sequential::Point &point,
                                                                                      const std::vector<mila::meanshift::sequential::Point> &points,
                                                                                      float bandwidth) {
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
