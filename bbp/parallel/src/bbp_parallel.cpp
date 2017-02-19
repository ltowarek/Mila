#include "bbp_parallel.hpp"
#include "bbp_parallel_profiler.hpp"

mila::ParallelBBP::ParallelBBP() : mila::ParallelBBP(nullptr, nullptr) {

}
mila::ParallelBBP::ParallelBBP(std::unique_ptr<OpenCLApplication> ocl_app,
                               const std::shared_ptr<Logger> logger) :
    source_file_path_("bbp.cl"),
    kernel_name_("bbp"),
    logger_(logger),
    ocl_app_(std::move(ocl_app)) {

}
mila::ParallelBBP::~ParallelBBP() {

}
void mila::ParallelBBP::Initialize() {
  kernel_ = ocl_app_->CreateKernel(kernel_name_, source_file_path_);
}
std::vector<float>
mila::ParallelBBP::ComputeDigits(const size_t number_of_digits, const size_t starting_position) {
  auto output = std::vector<cl_float>(number_of_digits, 0.0f);

  if (number_of_digits == 0) {
    return output;
  }

  auto output_buffer = CreateBuffer(output);
  kernel_.setArgs(static_cast<cl_uint>(starting_position), output_buffer);
  const auto global_work_size = std::vector<size_t>{number_of_digits};
  events_.enqueue_nd_range = ocl_app_->GetQueue().enqueueNDRangeKernel(kernel_, global_work_size);
  events_.read_buffer = ocl_app_->GetQueue().enqueueReadBuffer(output_buffer,
                                                               0,
                                                               output.size() * sizeof(output.at(0)),
                                                               output.data(),
                                                               {events_.enqueue_nd_range});

  return output;
}
clpp::Buffer mila::ParallelBBP::CreateBuffer(const std::vector<cl_float> output) const {
  return clpp::Buffer(ocl_app_->GetContext(), CL_MEM_WRITE_ONLY, output.size() * sizeof(output.at(0)));
}
mila::ParallelBBP::Events mila::ParallelBBP::GetEvents() const {
  return events_;
}

