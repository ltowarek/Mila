#include "mean_shift_parallel.h"

std::vector<cl_float4> mila::meanshift::parallel::ConvertVectorToPoints(const std::vector<uint8_t> &data) {
  auto output = std::vector<cl_float4>();

  if (data.size() % 4 != 0) {
    // TODO throw exception
    return output;
  }

  for (size_t i = 0; i < data.size(); i+=4) {
    auto point = cl_float4();
    point.x = static_cast<float>(data[i]);
    point.y = static_cast<float>(data[i+1]);
    point.z = static_cast<float>(data[i+2]);
    point.w = static_cast<float>(data[i+3]);
    output.push_back(point);
  }

  return output;
}

std::vector<uint8_t> mila::meanshift::parallel::ConvertPointsToVector(const std::vector<cl_float4> &data) {
  auto output = std::vector<uint8_t>();

  for (size_t i = 0; i < data.size(); ++i) {
    output.push_back(static_cast<uint8_t>(data[i].x));
    output.push_back(static_cast<uint8_t>(data[i].y));
    output.push_back(static_cast<uint8_t>(data[i].z));
    output.push_back(static_cast<uint8_t>(data[i].w));
  }

  return output;
}

mila::meanshift::parallel::MeanShift::MeanShift(): MeanShift(0, 0, 1e-5f, 100) {

}

mila::meanshift::parallel::MeanShift::MeanShift(size_t platform_id, size_t device_id): MeanShift(platform_id, device_id, 1e-5f, 100){

}

mila::meanshift::parallel::MeanShift::MeanShift(size_t platform_id,
                                                size_t device_id,
                                                float precision,
                                                size_t max_iterations): platform_id_(platform_id), device_id_(device_id), precision_(precision), max_iterations_(max_iterations) {

}

float mila::meanshift::parallel::MeanShift::precision() const {
  return precision_;
}

size_t mila::meanshift::parallel::MeanShift::max_iterations() const {
  return max_iterations_;
}

size_t mila::meanshift::parallel::MeanShift::platform_id() const {
  return platform_id_;
}

size_t mila::meanshift::parallel::MeanShift::device_id() const {
  return device_id_;
}
