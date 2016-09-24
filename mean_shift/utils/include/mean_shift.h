#ifndef MILA_UTILS_MEAN_SHIFT_H_
#define MILA_UTILS_MEAN_SHIFT_H_

#include <vector>

namespace mila {
struct Point {
  float x;
  float y;
  float z;
  float w;
};

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
