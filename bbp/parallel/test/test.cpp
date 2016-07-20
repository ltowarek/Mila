#include <chrono>
#include "gtest/gtest.h"
#include "bbp_parallel.h"
#include "bbp_parallel_profiler.h"

TEST(BBPParallelTest, DefaultConstructor) {
  mila::bbp::parallel::BBP bbp;
  EXPECT_EQ(bbp.precision(), 1e-5f);
  EXPECT_EQ(bbp.platform_id(), 0);
  EXPECT_EQ(bbp.device_id(), 0);
}

TEST(BBPParallelTest, PrecisionConstructor) {
  mila::bbp::parallel::BBP bbp(1e-7f);
  EXPECT_EQ(bbp.precision(), 1e-7f);
  EXPECT_EQ(bbp.platform_id(), 0);
  EXPECT_EQ(bbp.device_id(), 0);
}

TEST(BBPParallelTest, DeviceTypeConstructor) {
  mila::bbp::parallel::BBP bbp_0_0(0, 0);
  EXPECT_EQ(bbp_0_0.platform_id(), 0);
  EXPECT_EQ(bbp_0_0.device_id(), 0);
  EXPECT_EQ(bbp_0_0.precision(), 1e-5f);
  mila::bbp::parallel::BBP bbp_1_0(1, 0);
  EXPECT_EQ(bbp_1_0.platform_id(), 1);
  EXPECT_EQ(bbp_1_0.device_id(), 0);
  EXPECT_EQ(bbp_1_0.precision(), 1e-5f);
  mila::bbp::parallel::BBP bbp_0_1(0, 1);
  EXPECT_EQ(bbp_0_1.platform_id(), 0);
  EXPECT_EQ(bbp_0_1.device_id(), 1);
  EXPECT_EQ(bbp_0_1.precision(), 1e-5f);
}

TEST(BBPParallelTest, ComputeDigits) {
  mila::bbp::parallel::BBP bbp;
  EXPECT_EQ(bbp.ComputeDigits(0, 0).size(), 0);
  EXPECT_EQ(bbp.ComputeDigits(1, 0).size(), 1);
  ASSERT_EQ(bbp.ComputeDigits(2, 0).size(), 2);
  EXPECT_NEAR(bbp.ComputeDigits(2, 0)[0], 0.141587316989899f, 1e-5f);
  EXPECT_NEAR(bbp.ComputeDigits(2, 0)[1], 0.265479207038879f, 1e-5f);
  ASSERT_EQ(bbp.ComputeDigits(1, 1).size(), 1);
  EXPECT_NEAR(bbp.ComputeDigits(1, 1)[0], 0.265479207038879f, 1e-5f);
}

TEST(BBPParallelTest, ExecutionDevice) {
  auto platforms = clpp::Platform::get();
  for (size_t platform = 0; platform < platforms.size(); ++ platform) {
    auto devices = platforms[platform].getAllDevices();
    for (size_t device = 0; device < devices.size(); ++device) {
      mila::bbp::parallel::BBP bbp(platform, device);
      bbp.Run(0, 0);
      EXPECT_EQ(platforms[platform], bbp.platform());
      EXPECT_EQ(devices[device], bbp.device());
    }
  }
}

TEST(BBPParallelTest, Run) {
  mila::bbp::parallel::BBP bbp;
  EXPECT_EQ(bbp.Run(0, 0), "");
  EXPECT_EQ(bbp.Run(1, 0), "2");
  EXPECT_EQ(bbp.Run(2, 0), "24");
  EXPECT_EQ(bbp.Run(3, 0), "243");
  EXPECT_EQ(bbp.Run(4, 0), "243F");
  EXPECT_EQ(bbp.Run(5, 0), "243F6");
  EXPECT_EQ(bbp.Run(540, 0), "243F6A8885A308D313198A2E03707344A4093822299F31D0082EFA98EC4E6C89452821E638D01377BE5466"
      "CF34E90C6CC0AC29B7C97C50DD3F84D5B5B54709179216D5D98979FB1BD1310BA698DFB5AC2FFD72DBD01A"
      "DFB7B8E1AFED6A267E96BA7C9045F12C7F9924A19947B3916CF70801F2E2858EFC16636920D871574E69A4"
      "58FEA3F4933D7E0D95748F728EB658718BCD5882154AEE7B54A41DC25A59B59C30D5392AF26013C5D1B023"
      "286085F0CA417918B8DB38EF8E79DCB0603A180E6C9E0E8BB01E8A3ED71577C1BD314B2778AF2FDA55605C"
      "60E65525F3AA55AB945748986263E8144055CA396A2AAB10B6B4CC5C341141E8CEA15486AF7C72E993B3EE"
      "1411636FBC2A2BA9C55D7418");
  EXPECT_EQ(bbp.Run(24, 516), "1411636FBC2A2BA9C55D7418");
}

TEST(BBPParallelProfilerTest, DefaultConstructor) {
  mila::bbp::parallel::BBPProfiler bbp;
  EXPECT_EQ(bbp.precision(), 1e-5f);
  EXPECT_EQ(bbp.main_result(), "Digits per second");
  EXPECT_EQ(bbp.main_duration(), "Run");
}

TEST(BBPParallelProfilerTest, Constructor) {
  mila::bbp::parallel::BBPProfiler bbp(1e-7f);
  EXPECT_EQ(bbp.precision(), 1e-7f);
  EXPECT_EQ(bbp.main_result(), "Digits per second");
  EXPECT_EQ(bbp.main_duration(), "Run");
}

TEST(BBPParallelProfilerTest, Run) {
  mila::bbp::parallel::BBPProfiler bbp;
  EXPECT_EQ(bbp.Run(0, 0), "");
  EXPECT_EQ(bbp.Run(1, 0), "2");
  EXPECT_EQ(bbp.Run(2, 0), "24");
  EXPECT_EQ(bbp.Run(3, 0), "243");
  EXPECT_EQ(bbp.Run(4, 0), "243F");
  EXPECT_EQ(bbp.Run(5, 0), "243F6");
  EXPECT_EQ(bbp.Run(540, 0), "243F6A8885A308D313198A2E03707344A4093822299F31D0082EFA98EC4E6C89452821E638D01377BE5466"
      "CF34E90C6CC0AC29B7C97C50DD3F84D5B5B54709179216D5D98979FB1BD1310BA698DFB5AC2FFD72DBD01A"
      "DFB7B8E1AFED6A267E96BA7C9045F12C7F9924A19947B3916CF70801F2E2858EFC16636920D871574E69A4"
      "58FEA3F4933D7E0D95748F728EB658718BCD5882154AEE7B54A41DC25A59B59C30D5392AF26013C5D1B023"
      "286085F0CA417918B8DB38EF8E79DCB0603A180E6C9E0E8BB01E8A3ED71577C1BD314B2778AF2FDA55605C"
      "60E65525F3AA55AB945748986263E8144055CA396A2AAB10B6B4CC5C341141E8CEA15486AF7C72E993B3EE"
      "1411636FBC2A2BA9C55D7418");
  EXPECT_EQ(bbp.Run(24, 516), "1411636FBC2A2BA9C55D7418");
}

TEST(BBPParallelProfilerTest, RunWithProfiling) {
  mila::bbp::parallel::BBPProfiler bbp;
  EXPECT_EQ(bbp.results().count("Run"), 0);
  EXPECT_EQ(bbp.results().count("Digits per second"), 0);
  EXPECT_EQ(bbp.Run(24, 516), "1411636FBC2A2BA9C55D7418");
  EXPECT_EQ(bbp.results().count("Run"), 1);
  EXPECT_EQ(bbp.results().count("Digits per second"), 1);
}

TEST(BBPParallelProfilerTest, InitializeWithProfiling) {
  mila::bbp::parallel::BBPProfiler bbp;
  EXPECT_EQ(bbp.results().count("Initialize"), 0);
  bbp.Initialize();
  EXPECT_EQ(bbp.results().count("Initialize"), 1);
}

TEST(BBPParallelProfilerTest, GetBuildKernelAsMicroseconds) {
  auto bbp = mila::bbp::parallel::BBPProfiler();
  bbp.Initialize();
  EXPECT_GT(bbp.GetBuildKernelAsMicroseconds(), 0);
}

TEST(BBPParallelProfilerTest, GetReadBufferAsMicroseconds) {
  auto bbp = mila::bbp::parallel::BBPProfiler();
  bbp.Run(24, 516);
  EXPECT_GT(bbp.GetReadBufferAsMicroseconds(), 0);
}

TEST(BBPParallelProfilerTest, GetEnqueueNDRangeAsMicroseconds) {
  auto bbp = mila::bbp::parallel::BBPProfiler();
  bbp.Run(24, 516);
  EXPECT_GT(bbp.GetEnqueueNDRangeAsMicroseconds(), 0);
}

TEST(BBPParallelProfilerTest, GetOpenCLStatisticsAsString) {
  auto bbp = mila::bbp::parallel::BBPProfiler();
  EXPECT_STREQ("", bbp.GetOpenCLStatisticsAsString().c_str());
}

TEST(BBPParallelProfilerTest, GetOpenCLStatisticsAsStringWithRun) {
  auto bbp = mila::bbp::parallel::BBPProfiler();
  bbp.Run(24, 516);
  EXPECT_STRNE("", bbp.GetOpenCLStatisticsAsString().c_str());
}

TEST(BBPParallelProfilerTest, GetBandwidth) {
  auto bbp = mila::bbp::parallel::BBPProfiler();
  bbp.Run(24, 516);
  EXPECT_GT(bbp.GetBandwidth(), 0);
}

TEST(BBPParallelProfilerTest, TimersComparision) {
  const auto platforms = clpp::Platform::get();
  auto platform = platforms.at(0);

  const auto devices = platform.getAllDevices();
  auto device = devices.at(0);

  auto context = clpp::Context(device);
  auto queue = clpp::Queue(context, device, CL_QUEUE_PROFILING_ENABLE);

  const auto source_file_name = "bbp.cl";
  const auto kernel_name = std::string("bbp");
  auto source_file = mila::utils::ReadFile(source_file_name);
  auto program = clpp::Program(context, source_file);
  try {
    program.build(device);
  } catch(const clpp::Error& error) {
    printf("%s\n", program.getBuildLog(device).c_str());
  }
  auto kernel = clpp::Kernel(program, kernel_name.c_str());

  auto number_of_digits = size_t{1000};
  auto starting_position = 1000;
  auto output = std::vector<cl_float>(number_of_digits, 0.0f);

  auto output_buffer = clpp::Buffer(context, CL_MEM_WRITE_ONLY, output.size() * sizeof(output.at(0)));
  kernel.setArgs(starting_position, output_buffer);
  auto global_work_size = std::vector<size_t>{number_of_digits};
  queue.finish();

  auto start_time = std::chrono::high_resolution_clock::now();
  auto event = queue.enqueueNDRangeKernel(kernel, global_work_size);
  event.wait();
  auto end_time = std::chrono::high_resolution_clock::now();
  auto cpp_duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
  auto ocl_duration = (event.getProfilingCommandEnd() - event.getProfilingCommandStart()) / 1000;

  printf("OCL duration [us]: %lu\n", ocl_duration);
  printf("CPP duration [us]: %lu\n", cpp_duration);

  EXPECT_NEAR(ocl_duration, cpp_duration, 1000);  // Millisecond precision
}

