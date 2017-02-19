#ifndef MILA_UTILS_MEAN_SHIFT_H
#define MILA_UTILS_MEAN_SHIFT_H

#include <vector>
#include <memory>
#include <string>
#include <chrono>

namespace mila {
struct Point {
  float x;
  float y;
  float z;
  float w;
};

std::string to_string(const Point &p);
std::string to_string(const std::vector<Point> &v);
std::string to_string(const std::vector<std::chrono::microseconds> &v);

class MeanShift {
 public:
  virtual ~MeanShift() = 0;
  virtual std::vector<Point> Run(const std::vector<Point> &points, const float bandwidth) = 0;
};

class MeanShiftProfiler : public MeanShift {
 public:
  virtual ~MeanShiftProfiler() = 0;
};
}  // mila
#endif  // MILA_UTILS_MEAN_SHIFT_H
