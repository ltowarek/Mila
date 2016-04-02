#include "mean_shift_utils.h"

std::vector<uint8_t> mila::meanshift::utils::ReadPNGToVector(const std::string &file_name) {
  auto data = std::vector<uint8_t>();
  auto width = size_t{0};
  auto height = size_t{0};
  auto error = lodepng::decode(data, width, height, file_name);
  // TODO: Throw exception if error
  return data;
}

void mila::meanshift::utils::WriteVectorToPNG(const std::string &file_name, const std::vector<uint8_t> &data, uint8_t width, uint8_t height) {
  auto error = lodepng::encode(file_name, data, width, height);
  // TODO: Throw exception if error
}
