#include "mean_shift_sequential.h"

float mila::meanshift::sequential::Distance(const Point &point1, const Point &point2) {
  return sqrtf(powf(point1.x - point2.x, 2.0f) + powf(point1.y - point2.y, 2.0f) + powf(point1.z - point2.z, 2.0f));
}

float mila::meanshift::sequential::GaussianKernel(float x, float sigma) {
  float output = 0.0f;
  if (sigma != 0) {
    output = (1.0f / (sqrtf(2.0f * pi) * sigma)) * expf(-0.5f * powf(x / sigma, 2.0f));
  }
  return output;
}
