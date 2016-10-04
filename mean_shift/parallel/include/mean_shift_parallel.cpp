#include "mean_shift_parallel.h"

mila::ParallelMeanShift::ParallelMeanShift(): ParallelMeanShift(0, 0, 1e-5f, 100) {

}

mila::ParallelMeanShift::ParallelMeanShift(size_t platform_id, size_t device_id): ParallelMeanShift(platform_id, device_id, 1e-5f, 100){

}

mila::ParallelMeanShift::ParallelMeanShift(size_t platform_id,
                                                size_t device_id,
                                                float precision,
                                                size_t max_iterations): platform_id_(platform_id), device_id_(device_id), precision_(precision), max_iterations_(max_iterations) {

}

mila::ParallelMeanShift::~ParallelMeanShift() {

}

void mila::ParallelMeanShift::BuildProgram(const clpp::Program &program, const clpp::Device &device) {
  try {
    program.build(device);
  } catch(const clpp::Error& error) {
    printf("%s\n", program.getBuildLog(device).c_str());
  }
}

void mila::ParallelMeanShift::Initialize() {
  const auto platforms = clpp::Platform::get();
  platform_ = platforms.at(platform_id_);

  const auto devices = platform_.getAllDevices();
  device_ = devices.at(device_id_);

  context_ = clpp::Context(device_);
  queue_ = clpp::Queue(context_, device_, CL_QUEUE_PROFILING_ENABLE);

  const auto source_file_name = "mean_shift.cl";
  const auto kernel_name = std::string("MeanShift");
  auto source_file = mila::utils::ReadFile(source_file_name);
  auto program = clpp::Program(context_, source_file);

  BuildProgram(program, device_);
  kernel_ = clpp::Kernel(program, kernel_name.c_str());
}

std::vector<mila::Point> mila::ParallelMeanShift::Run(const std::vector<Point> &points,
                                                                 const float bandwidth) {
  Initialize();

  auto output = points;

  auto original_points_buffer = clpp::Buffer(context_, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, output.size() * sizeof(output.at(0)), output.data());
  auto current_points_buffer = clpp::Buffer(context_, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, output.size() * sizeof(output.at(0)), output.data());
  auto shifted_points_buffer = clpp::Buffer(context_, CL_MEM_WRITE_ONLY | CL_MEM_COPY_HOST_PTR, output.size() * sizeof(output.at(0)), output.data());

  auto distances = std::vector<cl_float>(output.size(), 0.0f);
  auto distances_buffer = clpp::Buffer(context_, CL_MEM_WRITE_ONLY, output.size() * sizeof(distances.at(0)));

  auto global_work_size = std::vector<size_t>{output.size()};
  auto difference_distance = 0.0f;
  auto iteration = size_t{0};

  do {
    auto copy_buffer_event = queue_.enqueueCopyBuffer(shifted_points_buffer, current_points_buffer, 0, 0, output.size() * sizeof(output.at(0)));
    kernel_.setArgs(current_points_buffer, original_points_buffer, static_cast<int>(output.size()), bandwidth, shifted_points_buffer, distances_buffer);
    auto enqueue_nd_range_event = queue_.enqueueNDRangeKernel(kernel_, global_work_size, std::vector<clpp::Event>{copy_buffer_event});
    auto read_buffer_event = queue_.enqueueReadBuffer(distances_buffer, 0, distances.size() * sizeof(distances.at(0)), distances.data(), {enqueue_nd_range_event});
    queue_.finish();
    difference_distance = *std::max_element(distances.begin(), distances.end());
    UpdateEvents(copy_buffer_event, enqueue_nd_range_event, read_buffer_event);
    ++iteration;
  } while ((difference_distance > precision_) && (iteration < max_iterations_));

  events_.read_buffer_with_output = queue_.enqueueReadBuffer(shifted_points_buffer, 0, output.size() * sizeof(output.at(0)), output.data());
  queue_.finish();

  return output;
}

void mila::ParallelMeanShift::UpdateEvents(clpp::Event copy_buffer, clpp::Event read_buffer, clpp::Event enqueue_nd_range) {
  events_.copy_buffer.push_back(copy_buffer);
  events_.read_buffer_with_distances.push_back(read_buffer);
  events_.enqueue_nd_range.push_back(enqueue_nd_range);
}
