#ifndef MILA_MEAN_SHIFT_SEQUENTIAL_H_
#define MILA_MEAN_SHIFT_SEQUENTIAL_H_

#include <math.h>

namespace mila {
namespace meanshift {
namespace sequential {
  struct Point {
    float x;
    float y;
    float z;
    float w;
  };

  float Distance(const Point &point1, const Point &point2);
}  // sequential
}  // meanshift
}  // mila
#endif  // MILA_MEAN_SHIFT_SEQUENTIAL_H_
