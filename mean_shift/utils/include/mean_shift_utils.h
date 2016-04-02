#ifndef MILA_MEAN_SHIFT_UTILS_H_
#define MILA_MEAN_SHIFT_UTILS_H_

#include <cstdint>
#include <string>
#include <vector>

#include "lodepng.h"

namespace mila {
namespace meanshift {
namespace utils {

std::vector<uint8_t> ReadPNGToVector(const std::string &file_name);
void WriteVectorToPNG(const std::string &file_name, const std::vector<uint8_t> &data, uint8_t width, uint8_t height);

}  // utils
}  // meanshift
}  // mila

#endif  // MILA_MEAN_SHIFT_UTILS_H_
