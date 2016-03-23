#include "bbp_parallel.h"

mila::bbp::parallel::BBP::BBP() : BBP(1e-5f) {
}

mila::bbp::parallel::BBP::BBP(float precision) : precision_(precision) {
}

mila::bbp::parallel::BBP::~BBP() {
}

float mila::bbp::parallel::BBP::precision() const {
  return precision_;
}

clpp::Platform mila::bbp::parallel::BBP::platform() const {
  return platform_;
}

clpp::Device mila::bbp::parallel::BBP::device() const {
  return device_;
}

clpp::Context mila::bbp::parallel::BBP::context() const {
  return context_;
}

clpp::Queue mila::bbp::parallel::BBP::queue() const {
  return queue_;
}

clpp::Kernel mila::bbp::parallel::BBP::kernel() const {
  return kernel_;
}

void mila::bbp::parallel::BBP::Initialize() {
  const auto platforms = clpp::Platform::get();
  const auto platform_id = size_t{0};
  platform_ = platforms.at(platform_id);

  const auto devices = platform_.getAllDevices();
  const auto device_id = size_t{0};
  device_ = devices.at(device_id);

  context_ = clpp::Context(device_);
  queue_ = clpp::Queue(context_, device_);

  const auto source_file_name = "bbp.cl";
  const auto kernel_name = std::string("bbp");
  auto source_file = ReadFile(source_file_name);
  auto program = clpp::Program(context_, source_file);
  program.build(device_);
  kernel_ = clpp::Kernel(program, kernel_name.c_str());
}

std::string mila::bbp::parallel::BBP::ReadFile(const std::string &file) const {
  std::ifstream in(file);
  auto content = std::string(std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>());
  return content;
}

std::vector<float> mila::bbp::parallel::BBP::ComputeDigits(size_t number_of_digits, size_t starting_position) {
  Initialize();
  auto output = std::vector<cl_float>(number_of_digits, 0.0f);

  if (number_of_digits == 0) {
    return output;
  }

  auto output_buffer = clpp::Buffer(context_, CL_MEM_WRITE_ONLY, output.size() * sizeof(output.at(0)));
  kernel_.setArgs(starting_position, output_buffer);
  auto global_work_size = std::vector<size_t>{number_of_digits};
  queue_.enqueueNDRangeKernel(kernel_, global_work_size).wait();
  queue_.readBuffer(output_buffer, 0, output.size() * sizeof(output.at(0)), output.data());

  return output;
}

std::string mila::bbp::parallel::BBP::Run(size_t number_of_digits, size_t starting_position) {
  auto digits = ComputeDigits(number_of_digits, starting_position);
  auto hex_digits = mila::bbp::utils::ConvertFractionsToHex(digits, 1);
  auto output = std::string("");
  for (auto digit : hex_digits) {
    output += digit[0];
  }
  return output;
}
