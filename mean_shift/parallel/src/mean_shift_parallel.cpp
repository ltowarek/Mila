#include "mean_shift_parallel.hpp"

mila::ParallelMeanShift::ParallelMeanShift(std::unique_ptr<mila::OpenCLApplication> ocl_app,
                                           const std::shared_ptr<mila::Logger> logger)
    : ocl_app_(std::move(ocl_app)), logger_(logger) {

}

mila::ParallelMeanShift::~ParallelMeanShift() {

}

void mila::ParallelMeanShift::Initialize() {
  kernel_ = ocl_app_->CreateKernel("MeanShift", "mean_shift.cl");
}

std::vector<mila::Point> mila::ParallelMeanShift::Run(const std::vector<Point> &points,
                                                      const float bandwidth) {
  const auto precision = 1e-5f;
  const auto max_iterations = 100;

  auto output = points;
  auto distances = std::vector<cl_float>(output.size(), 0.0f);

  const auto original_points_buffer = clpp::Buffer(ocl_app_->GetContext(),
                                                   CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                                   output.size() * sizeof(output[0]),
                                                   output.data());
  const auto current_points_buffer = clpp::Buffer(ocl_app_->GetContext(),
                                                  CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                                  output.size() * sizeof(output[0]),
                                                  output.data());
  const auto shifted_points_buffer = clpp::Buffer(ocl_app_->GetContext(),
                                                  CL_MEM_WRITE_ONLY | CL_MEM_COPY_HOST_PTR,
                                                  output.size() * sizeof(output[0]),
                                                  output.data());
  const auto distances_buffer = clpp::Buffer(ocl_app_->GetContext(),
                                             CL_MEM_WRITE_ONLY,
                                             distances.size() * sizeof(distances[0]));

  const auto global_work_size = std::vector<size_t>{output.size()};
  auto iteration = size_t{0};
  auto difference_distance = 0.0f;

  do {
    auto copy_buffer_event = ocl_app_->GetQueue().enqueueCopyBuffer(shifted_points_buffer,
                                                                    current_points_buffer,
                                                                    0,
                                                                    0,
                                                                    output.size() * sizeof(output[0]));

    kernel_.setArgs(current_points_buffer,
                    original_points_buffer,
                    static_cast<int>(output.size()),
                    bandwidth,
                    shifted_points_buffer,
                    distances_buffer);
    auto enqueue_nd_range_event = ocl_app_->GetQueue().enqueueNDRangeKernel(kernel_,
                                                                            global_work_size,
                                                                            std::vector<clpp::Event>{
                                                                                copy_buffer_event});
    auto read_buffer_event = ocl_app_->GetQueue().enqueueReadBuffer(distances_buffer,
                                                                    0,
                                                                    distances.size() * sizeof(distances[0]),
                                                                    distances.data(),
                                                                    {enqueue_nd_range_event});
    ocl_app_->GetQueue().finish();

    SaveEvents(copy_buffer_event, enqueue_nd_range_event, read_buffer_event);
    difference_distance = *std::max_element(distances.begin(), distances.end());
    ++iteration;
  } while ((difference_distance > precision) && (iteration < max_iterations));

  events_.read_buffer_with_output = ocl_app_->GetQueue().enqueueReadBuffer(shifted_points_buffer,
                                                                           0,
                                                                           output.size() * sizeof(output[0]),
                                                                           output.data());
  ocl_app_->GetQueue().finish();

  return output;
}

void mila::ParallelMeanShift::SaveEvents(clpp::Event copy_buffer,
                                         clpp::Event read_buffer,
                                         clpp::Event enqueue_nd_range) {
  events_.copy_buffer.push_back(copy_buffer);
  events_.read_buffer_with_distances.push_back(read_buffer);
  events_.enqueue_nd_range.push_back(enqueue_nd_range);
}

mila::ParallelMeanShift::Events mila::ParallelMeanShift::GetEvents() const {
  return events_;
}
