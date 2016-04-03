#include "mean_shift_parallel.h"

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
