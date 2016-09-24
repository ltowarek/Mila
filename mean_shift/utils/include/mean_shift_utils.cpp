#include "mean_shift_utils.h"

mila::Image::Image(): Image("") {}

mila::Image::Image(const std::string &file_name): width_(0), height_(0), file_name_(file_name) {}

std::vector<uint8_t> mila::Image::Read() {
  auto data = std::vector<uint8_t>();
  auto error = lodepng::decode(data, width_, height_, file_name_.c_str());
  // TODO: Throw exception if error
  return data;
}

void mila::Image::Write(const std::vector<uint8_t> &data, uint32_t width, uint32_t height) {
  width_ = width;
  height_ = height;
  auto error = lodepng::encode(file_name_.c_str(), data, width_, height_);
  // TODO: Throw exception if error
}

uint32_t mila::Image::width() const {
  return width_;
}

uint32_t mila::Image::height() const {
  return height_;
}

std::string mila::Image::file_name() const {
  return file_name_;
}
