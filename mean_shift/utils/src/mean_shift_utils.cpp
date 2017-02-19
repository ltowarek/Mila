#include "mean_shift_utils.hpp"

std::vector<mila::Point> mila::ConvertVectorToPoints(const std::vector<uint8_t> &data) {
  auto output = std::vector<Point>();

  if (data.size() % 4 != 0) {
    throw std::runtime_error("Vector size is not divisible by 4");
  }

  for (size_t i = 0; i < data.size(); i += 4) {
    auto point = Point();
    point.x = static_cast<float>(data[i]);
    point.y = static_cast<float>(data[i + 1]);
    point.z = static_cast<float>(data[i + 2]);
    point.w = static_cast<float>(data[i + 3]);
    output.push_back(point);
  }

  return output;
}

std::vector<uint8_t> mila::ConvertPointsToVector(const std::vector<Point> &data) {
  auto output = std::vector<uint8_t>();

  for (size_t i = 0; i < data.size(); ++i) {
    output.push_back(static_cast<uint8_t>(data[i].x));
    output.push_back(static_cast<uint8_t>(data[i].y));
    output.push_back(static_cast<uint8_t>(data[i].z));
    output.push_back(static_cast<uint8_t>(data[i].w));
  }

  return output;
}

mila::Image::Image(): Image("") {}

mila::Image::Image(const std::string &file_name): width_(0), height_(0), file_name_(file_name) {}

std::vector<uint8_t> mila::Image::Read() {
  auto data = std::vector<uint8_t>();
  auto error = lodepng::decode(data, width_, height_, file_name_.c_str());
  if (error) {
    throw std::runtime_error(std::string("Failed to decode an image: ") + lodepng_error_text(error));
  }
  return data;
}

void mila::Image::Write(const std::vector<uint8_t> &data, uint32_t width, uint32_t height) {
  width_ = width;
  height_ = height;
  auto error = lodepng::encode(file_name_.c_str(), data, width_, height_);
  if (error) {
    throw std::runtime_error(std::string("Failed to encode an image: ") + lodepng_error_text(error));
  }
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
