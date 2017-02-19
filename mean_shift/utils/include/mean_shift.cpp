#include "mean_shift.h"

std::string mila::to_string(const mila::Point &p) {
  return std::to_string(p.x) + " " + std::to_string(p.y) + " " + std::to_string(p.z) + " " + std::to_string(p.w);
}

std::string mila::to_string(const std::vector<mila::Point> &v) {
  auto s = std::string("");
  for (const auto &p : v) {
    s += mila::to_string(p) + "\n";
  }
  return s;
}

std::string mila::to_string(const std::vector<std::chrono::microseconds> &v) {
  auto s = std::string("");
  for (const auto &e : v) {
    s += e.count() + "us ";
  }
  s += "\n";
  return s;
}

mila::MeanShift::~MeanShift() {

}

mila::MeanShiftProfiler::~MeanShiftProfiler() {

}
