#ifndef MILA_MEAN_SHIFT_SEQUENTIAL_H_
#define MILA_MEAN_SHIFT_SEQUENTIAL_H_

#include <cmath>
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

float Distance(const Point &point1, const Point &point2);
float GaussianKernel(float x, float sigma);

class MeanShift {
 public:
  Point ShiftPoint(const Point &point, const std::vector<Point> &points, float bandwidth);
};
}  // sequential
}  // meanshift
}  // mila
#endif  // MILA_MEAN_SHIFT_SEQUENTIAL_H_
