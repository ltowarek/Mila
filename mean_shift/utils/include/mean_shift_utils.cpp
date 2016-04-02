#include "mean_shift_utils.h"

mila::meanshift::utils::Image::Image(): Image("") {}

mila::meanshift::utils::Image::Image(const std::string &file_name): width_(0), height_(0), file_name_(file_name) {}

std::vector<uint8_t> mila::meanshift::utils::Image::Read() {
  auto data = std::vector<uint8_t>();
  auto error = lodepng::decode(data, width_, height_, file_name_);
  // TODO: Throw exception if error
  return data;
}

void mila::meanshift::utils::Image::Write(const std::vector<uint8_t> &data, uint8_t width, uint8_t height) {
  width_ = width;
  height_ = height;
  auto error = lodepng::encode(file_name_, data, width_, height_);
  // TODO: Throw exception if error
}

size_t mila::meanshift::utils::Image::width() const {
  return width_;
}

size_t mila::meanshift::utils::Image::height() const {
  return height_;
}

std::string mila::meanshift::utils::Image::file_name() const {
  return file_name_;
}
