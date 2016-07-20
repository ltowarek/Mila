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

clpp::Platform mila::meanshift::parallel::MeanShift::platform() const {
  return platform_;
}

clpp::Device mila::meanshift::parallel::MeanShift::device() const {
  return device_;
}

clpp::Context mila::meanshift::parallel::MeanShift::context() const {
  return context_;
}

clpp::Queue mila::meanshift::parallel::MeanShift::queue() const {
  return queue_;
}

clpp::Kernel mila::meanshift::parallel::MeanShift::kernel() const {
  return kernel_;
}

void mila::meanshift::parallel::MeanShift::BuildProgram(const clpp::Program &program, const clpp::Device &device) {
  try {
    program.build(device);
  } catch(const clpp::Error& error) {
    printf("%s\n", program.getBuildLog(device).c_str());
  }
}

void mila::meanshift::parallel::MeanShift::Initialize() {
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

std::vector<cl_float4> mila::meanshift::parallel::MeanShift::Run(const std::vector<cl_float4> &points,
                                                                 float bandwidth) {
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

void mila::meanshift::parallel::MeanShift::UpdateEvents(clpp::Event copy_buffer, clpp::Event read_buffer, clpp::Event enqueue_nd_range) {
  events_.copy_buffer.push_back(copy_buffer);
  events_.read_buffer_with_distances.push_back(read_buffer);
  events_.enqueue_nd_range.push_back(enqueue_nd_range);
}

mila::meanshift::parallel::MeanShiftImageProcessing::MeanShiftImageProcessing(): MeanShift() {

}

mila::meanshift::parallel::MeanShiftImageProcessing::MeanShiftImageProcessing(size_t platform_id, size_t device_id): MeanShift(platform_id, device_id) {

}

mila::meanshift::parallel::MeanShiftImageProcessing::MeanShiftImageProcessing(size_t platform_id,
                                                                              size_t device_id,
                                                                              float precision,
                                                                              size_t max_iterations): MeanShift(platform_id, device_id, precision, max_iterations) {

}

std::vector<cl_float4> mila::meanshift::parallel::MeanShiftImageProcessing::Run(const std::vector<cl_float4> &points,
                                                                                float bandwidth) {
  return MeanShift::Run(points, bandwidth);
}

void mila::meanshift::parallel::MeanShiftImageProcessing::Run(const std::string &input_file,
                                                              const std::string &output_file,
                                                              float bandwidth) {
  auto input_image = mila::meanshift::utils::Image(input_file);
  auto output_image = mila::meanshift::utils::Image(output_file);

  auto input_data = input_image.Read();
  auto input_points = ConvertVectorToPoints(input_data);
  auto output_points = Run(input_points, bandwidth);
  for (size_t i = 0; i < output_points.size(); ++i) {
    output_points[i].w = 255;
  }
  auto output_data = ConvertPointsToVector(output_points);

  output_image.Write(output_data, input_image.width(), input_image.height());
}
