#ifndef MILA_MEAN_SHIFT_UTILS_H_
#define MILA_MEAN_SHIFT_UTILS_H_

#include <cstdint>
#include <string>
#include <vector>

#include "lodepng.h"

namespace mila {

class Image {
 public:
  Image();
  Image(const std::string &file_name);

  std::vector<uint8_t> Read();
  void Write(const std::vector<uint8_t> &data, uint32_t width, uint32_t height);

  uint32_t width() const;
  uint32_t height() const;
  std::string file_name() const;
 private:
  uint32_t width_;
  uint32_t height_;
  std::string file_name_;
};

}  // mila

#endif  // MILA_MEAN_SHIFT_UTILS_H_
