#ifndef MILA_MEAN_SHIFT_UTILS_H_
#define MILA_MEAN_SHIFT_UTILS_H_

#include <cstdint>
#include <string>
#include <vector>

#include "lodepng.h"

namespace mila {
namespace meanshift {
namespace utils {

class Image {
 public:
  Image();
  Image(const std::string &file_name);

  std::vector<uint8_t> Read();
  void Write(const std::vector<uint8_t> &data, size_t width, size_t height);

  size_t width() const;
  size_t height() const;
  std::string file_name() const;
 private:
  size_t width_;
  size_t height_;
  std::string file_name_;
};

}  // utils
}  // meanshift
}  // mila

#endif  // MILA_MEAN_SHIFT_UTILS_H_
