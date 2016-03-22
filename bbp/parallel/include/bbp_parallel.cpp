#include "bbp_parallel.h"

mila::bbp::parallel::BBP::BBP() : BBP(nullptr, nullptr, nullptr, nullptr, 1e-5f)
{
}

mila::bbp::parallel::BBP::BBP(float precision) : BBP(nullptr, nullptr, nullptr, nullptr, precision) {

}

mila::bbp::parallel::BBP::BBP(cl_platform_id platform,
                              cl_device_id device,
                              cl_context context,
                              cl_command_queue queue,
                              float precision) : platform_(platform),
                                                 device_(device),
                                                 context_(context),
                                                 queue_(queue),
                                                 precision_(precision)
{
}

float mila::bbp::parallel::BBP::precision() const {
  return precision_;
}

cl_platform_id mila::bbp::parallel::BBP::platform() const {
  return platform_;
}

cl_device_id mila::bbp::parallel::BBP::device() const {
  return device_;
}

cl_context mila::bbp::parallel::BBP::context() const {
  return context_;
}

cl_command_queue mila::bbp::parallel::BBP::queue() const {
  return queue_;
}

void mila::bbp::parallel::BBP::Initialize() {

}
