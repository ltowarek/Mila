#include "mean_shift_sequential.h"

float mila::meanshift::sequential::Distance(const Point &point1, const Point &point2) {
  return sqrtf(powf(point1.x - point2.x, 2.0f) + powf(point1.y - point2.y, 2.0f) + powf(point1.z - point2.z, 2.0f));
}
