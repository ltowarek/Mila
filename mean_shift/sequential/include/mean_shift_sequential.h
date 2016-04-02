#ifndef MILA_MEAN_SHIFT_SEQUENTIAL_H_
#define MILA_MEAN_SHIFT_SEQUENTIAL_H_

#include <cmath>
#include <cstdint>
#include <cstddef>
#include <vector>

namespace mila {
namespace meanshift {
namespace sequential {
const float pi = 3.14159265358979323846f;

struct Point {
  float x;
  float y;
  float z;
  float w;
};

std::vector<Point> ConvertVectorToPoints(const std::vector<uint8_t> &data);
std::vector<uint8_t> ConvertPointsToVector(const std::vector<Point> &data);

float Distance(const Point &point1, const Point &point2);
float GaussianKernel(float x, float sigma);

class MeanShift {
 public:
  MeanShift();
  MeanShift(float precision, size_t max_iterations);

  Point ShiftPoint(const Point &point, const std::vector<Point> &points, float bandwidth) const;
  std::vector<Point> Run(const std::vector<Point> &points, float bandwidth) const;

  float precision() const;
  size_t max_iterations() const;
 private:
  const float precision_;
  const size_t max_iterations_;
};
}  // sequential
}  // meanshift
}  // mila
#endif  // MILA_MEAN_SHIFT_SEQUENTIAL_H_
