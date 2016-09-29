#ifndef MILA_UTILS_MEAN_SHIFT_H_
#define MILA_UTILS_MEAN_SHIFT_H_

#include <vector>
#include <memory>
#include <string>

namespace mila {
struct Point {
  float x;
  float y;
  float z;
  float w;
};

std::string to_string(const Point &p);
std::string to_string(const std::vector<Point> &v);

class MeanShift {
 public:
  virtual ~MeanShift() = 0;
  virtual std::vector<Point> Run(const std::vector<Point> &points, const float bandwidth) = 0;
};

class MeanShiftProfiler : public MeanShift {
 public:
  virtual ~MeanShiftProfiler() = 0;
};

class MeanShiftApp {
 public:
  virtual ~MeanShiftApp() = 0;
  virtual void Run(int argc, char **argv) const = 0;
};
}  // mila
#endif  // MILA_UTILS_MEAN_SHIFT_H_
