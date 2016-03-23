#include "bbp_parallel.h"

mila::bbp::parallel::BBP::BBP() : BBP(1e-5f) {
}

mila::bbp::parallel::BBP::BBP(float precision) : platform_(nullptr),
                                                 device_(nullptr),
                                                 context_(nullptr),
                                                 queue_(nullptr),
                                                 kernel_(nullptr),
                                                 precision_(precision) {
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
  auto error = cl_int{0};

  auto number_of_platforms = cl_uint{0};

  error = clGetPlatformIDs(0, nullptr, &number_of_platforms);
  if (error) {
    printf("Failed to get number of available platforms\n");
  }

  auto platforms = std::vector<cl_platform_id>(number_of_platforms);

  error = clGetPlatformIDs(number_of_platforms, platforms.data(), nullptr);
  if (error) {
    printf("Failed to get platform ids\n");
  }

  const auto platform_id = size_t{0};
  platform_ = platforms.at(platform_id);

  auto number_of_devices = cl_uint{0};
  const auto device_type = cl_device_type{CL_DEVICE_TYPE_ALL};
  error = clGetDeviceIDs(platform_, device_type, 0, nullptr, &number_of_devices);
  if (error) {
    printf("Failed to get number of available devices\n");
  }

  auto devices = std::vector<cl_device_id>(number_of_devices);

  error = clGetDeviceIDs(platform_, device_type, number_of_devices, devices.data(), nullptr);
  if (error) {
    printf("Failed to get device ids\n");
  }

  const auto device_id = size_t{0};
  device_ = devices.at(device_id);
  devices.clear();
  devices.push_back(device_);

  auto device_name_length = size_t{0};
  error = clGetDeviceInfo(device_, CL_DEVICE_NAME, 0, nullptr, &device_name_length);
  if (error) {
    printf("Failed to get device name size\n");
  }

  auto device_name = std::vector<char>(device_name_length);

  error = clGetDeviceInfo(device_, CL_DEVICE_NAME, device_name_length, device_name.data(), nullptr);
  if (error) {
    printf("Failed to get device name\n");
  }

  const auto properties =
      std::vector<cl_context_properties>{CL_CONTEXT_PLATFORM, reinterpret_cast<cl_context_properties>(platform_), 0};

  context_ = clCreateContext(properties.data(), devices.size(), devices.data(), nullptr, nullptr, &error);
  if (error) {
    printf("Failed to create the context\n");
  }

  auto queue_properties = cl_command_queue_properties{CL_QUEUE_PROFILING_ENABLE};

  queue_ = clCreateCommandQueue(context_, device_, queue_properties, &error);
  if (error) {
    printf("Failed to create the command queue\n");
  }

  const auto source_file_name = "bbp.cl";
  const auto kernel_name = std::string("bbp");
  kernel_ = CreateKernel(source_file_name, kernel_name);
}

mila::bbp::parallel::BBP::~BBP() {
  clReleaseCommandQueue(queue_);
  clReleaseContext(context_);
}

cl_kernel mila::bbp::parallel::BBP::kernel() const {
  return kernel_;
}

cl_kernel mila::bbp::parallel::BBP::CreateKernel(const std::string &kernel_file, const std::string &kernel_name) const {
  auto source_program = ReadFile(kernel_file);
  auto program = CreateProgram(source_program);
  BuildProgram(program);

  auto error = cl_int{0};
  auto kernel = clCreateKernel(program, kernel_name.data(), &error);
  if (error) {
    printf("Failed to create the kernel\n");
  }

  return kernel;
}

void mila::bbp::parallel::BBP::BuildProgram(const cl_program& program) const {
  auto error = cl_int{0};
  const auto options = std::string("");
  error = clBuildProgram(program, 1, &device_, options.data(), nullptr, nullptr);
  if (error) {
    printf("Failed to build the program\n");

    if (error == CL_BUILD_PROGRAM_FAILURE) {
      auto build_log_length = size_t{0};
      error = clGetProgramBuildInfo(program, device_, CL_PROGRAM_BUILD_LOG, 0, nullptr, &build_log_length);
      if (error) {
        printf("Failed to get build log length\n");
      }

      auto build_log = std::vector<char>(build_log_length);
      error = clGetProgramBuildInfo(program,
                                    device_, CL_PROGRAM_BUILD_LOG, build_log_length, build_log.data(), nullptr);
      if (error) {
        printf("Failed to get build log\n");
      }

      printf("%s\n", build_log.data());
    }
  }
}

cl_program mila::bbp::parallel::BBP::CreateProgram(const std::string &program_source) const {
  auto error = cl_int{0};
  const auto source_program_size = program_source.size();
  const char* strings = program_source.data();
  cl_program program = clCreateProgramWithSource(context_, 1, &strings, &source_program_size, &error);
  if (error) {
    printf("Failed to create the source program\n");
  }
  return program;
}

std::string mila::bbp::parallel::BBP::ReadFile(const std::string &file) const {
  std::ifstream in(file);
  auto content = std::string(std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>());
  return content;
}
