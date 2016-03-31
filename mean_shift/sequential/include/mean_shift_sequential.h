#ifndef MILA_MEAN_SHIFT_SEQUENTIAL_H_
#define MILA_MEAN_SHIFT_SEQUENTIAL_H_

#include <math.h>

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
}  // sequential
}  // meanshift
}  // mila
#endif  // MILA_MEAN_SHIFT_SEQUENTIAL_H_
