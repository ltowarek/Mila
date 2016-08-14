#include <chrono>
#include <list>
#include "gtest/gtest.h"
#include "bbp_parallel.h"
#include "bbp_parallel_profiler.h"

template<typename T>
std::unique_ptr<mila::BBP> CreateBBP();

template<>
std::unique_ptr<mila::BBP> CreateBBP<mila::ParallelBBP>() {
  auto ocl_app = mila::OpenCLApplicationFactory().MakeGeneric(0, 0, nullptr);
  return mila::BBPFactory().MakeParallel(std::move(ocl_app), nullptr);
}

template<>
std::unique_ptr<mila::BBP> CreateBBP<mila::GenericBBPProfiler>() {
  auto bbp = CreateBBP<mila::ParallelBBP>();
  auto profiler = mila::ProfilerFactory().MakeChrono(nullptr);
  return mila::BBPFactory().MakeGenericBBPProfiler(std::move(bbp), std::move(profiler), nullptr);
}

template<>
std::unique_ptr<mila::BBP> CreateBBP<mila::ParallelBBPProfiler>() {
  auto ocl_app = mila::OpenCLApplicationFactory().MakeGeneric(0, 0, nullptr);
  auto profiler = mila::ProfilerFactory().MakeChrono(nullptr);
  return mila::BBPFactory().MakeParallelBBPProfiler(std::move(ocl_app), std::move(profiler), nullptr);
}

template<typename T>
class BBPTest: public testing::Test {
 protected:
  BBPTest() : bbp_(std::move(CreateBBP<T>())) {}
  std::unique_ptr<mila::BBP> bbp_;
};

typedef testing::Types<mila::ParallelBBP,
                       mila::GenericBBPProfiler,
                       mila::ParallelBBPProfiler> BBPImplementations;

TYPED_TEST_CASE(BBPTest, BBPImplementations);

TYPED_TEST(BBPTest, ComputeDigits) {
  EXPECT_EQ(this->bbp_->ComputeDigits(0, 0).size(), 0);
  EXPECT_EQ(this->bbp_->ComputeDigits(1, 0).size(), 1);
  ASSERT_EQ(this->bbp_->ComputeDigits(2, 0).size(), 2);
  EXPECT_NEAR(this->bbp_->ComputeDigits(2, 0)[0], 0.141587316989899f, 1e-5f);
  EXPECT_NEAR(this->bbp_->ComputeDigits(2, 0)[1], 0.265479207038879f, 1e-5f);
  ASSERT_EQ(this->bbp_->ComputeDigits(1, 1).size(), 1);
  EXPECT_NEAR(this->bbp_->ComputeDigits(1, 1)[0], 0.265479207038879f, 1e-5f);
}

TYPED_TEST(BBPTest, GetDigits) {
  EXPECT_EQ(this->bbp_->GetDigits(this->bbp_->ComputeDigits(0, 0)), "");
  EXPECT_EQ(this->bbp_->GetDigits(this->bbp_->ComputeDigits(1, 0)), "2");
  EXPECT_EQ(this->bbp_->GetDigits(this->bbp_->ComputeDigits(2, 0)), "24");
  EXPECT_EQ(this->bbp_->GetDigits(this->bbp_->ComputeDigits(3, 0)), "243");
  EXPECT_EQ(this->bbp_->GetDigits(this->bbp_->ComputeDigits(4, 0)), "243F");
  EXPECT_EQ(this->bbp_->GetDigits(this->bbp_->ComputeDigits(5, 0)), "243F6");
  EXPECT_EQ(this->bbp_->GetDigits(this->bbp_->ComputeDigits(540, 0)),
            "243F6A8885A308D313198A2E03707344A4093822299F31D0082EFA98EC4E6C89452821E638D01377BE5466"
                "CF34E90C6CC0AC29B7C97C50DD3F84D5B5B54709179216D5D98979FB1BD1310BA698DFB5AC2FFD72DBD01A"
                "DFB7B8E1AFED6A267E96BA7C9045F12C7F9924A19947B3916CF70801F2E2858EFC16636920D871574E69A4"
                "58FEA3F4933D7E0D95748F728EB658718BCD5882154AEE7B54A41DC25A59B59C30D5392AF26013C5D1B023"
                "286085F0CA417918B8DB38EF8E79DCB0603A180E6C9E0E8BB01E8A3ED71577C1BD314B2778AF2FDA55605C"
                "60E65525F3AA55AB945748986263E8144055CA396A2AAB10B6B4CC5C341141E8CEA15486AF7C72E993B3EE"
                "1411636FBC2A2BA9C55D7418");
  EXPECT_EQ(this->bbp_->GetDigits(this->bbp_->ComputeDigits(24, 516)), "1411636FBC2A2BA9C55D7418");
}

template<typename T>
std::unique_ptr<mila::BBPProfiler> CreateBBPProfiler();

template<>
std::unique_ptr<mila::BBPProfiler>
CreateBBPProfiler<mila::GenericBBPProfiler>() {
  auto ocl_app = mila::OpenCLApplicationFactory().MakeGeneric(0, 0, nullptr);
  auto profiler = mila::ProfilerFactory().MakeChrono(nullptr);
  auto bbp = mila::BBPFactory().MakeParallel(std::move(ocl_app), nullptr);
  return mila::BBPProfilerFactory().MakeGeneric(std::move(bbp), std::move(profiler), nullptr);
}

template<>
std::unique_ptr<mila::BBPProfiler>
CreateBBPProfiler<mila::ParallelBBPProfiler>() {
  auto ocl_app = mila::OpenCLApplicationFactory().MakeGeneric(0, 0, nullptr);
  auto profiler = mila::ProfilerFactory().MakeChrono(nullptr);
  return mila::BBPProfilerFactory().MakeParallel(std::move(ocl_app),
                                                          std::move(profiler),
                                                          nullptr);
}

template<typename T>
std::unique_ptr<mila::Profiler> CreateProfiler();

template<>
std::unique_ptr<mila::Profiler> CreateProfiler<mila::ChronoProfiler>() {
  return mila::ProfilerFactory().MakeChrono(nullptr);
}

template<typename T>
class ProfilerTest: public testing::Test {
 protected:
  ProfilerTest() : profiler_(std::move(CreateProfiler<T>())) {}
  std::unique_ptr<mila::Profiler> profiler_;
};

typedef testing::Types<mila::ChronoProfiler> ProfilerImplementations;

TYPED_TEST_CASE(ProfilerTest, ProfilerImplementations);

TYPED_TEST(ProfilerTest, Workflow) {
  EXPECT_EQ(this->profiler_->GetDuration("Test").count(), 0.0f);
  this->profiler_->Start("Test");
  sleep(1);
  this->profiler_->End("Test");
  EXPECT_GT(this->profiler_->GetDuration("Test").count(), 0.0f);
}

class ProfilerStub: public mila::Profiler {
 public:
  virtual ~ProfilerStub() override {

  }
  virtual void Start(const std::string &event_name) override {

  }
  virtual void End(const std::string &event_name) override {

  }
  virtual std::chrono::duration<long int, std::micro> GetDuration(const std::string &event_name) const override {
    return std::chrono::microseconds(1);
  }

};

class ParallelBBPProfilerTest: public testing::Test {
 protected:
  virtual void SetUp() {
    auto ocl_app = mila::OpenCLApplicationFactory().MakeGeneric(0, 0, nullptr);
    auto profiler = std::unique_ptr<mila::Profiler>(new ProfilerStub());
    auto bbp = std::unique_ptr<mila::ParallelBBP>(new mila::ParallelBBP(move(ocl_app),
                                                                        nullptr));
    auto bbp_profiler = new mila::ParallelBBPProfiler(std::move(bbp), std::move(profiler), nullptr);
    bbp_ = std::unique_ptr<mila::ParallelBBPProfiler>(bbp_profiler);
  }
  std::unique_ptr<mila::ParallelBBPProfiler> bbp_;
};

TEST_F(ParallelBBPProfilerTest, GetResultsAfterInitialize) {
  this->bbp_->Initialize();
  EXPECT_GT(this->bbp_->GetResults().initialize_duration.count(), 0);
  EXPECT_GT(this->bbp_->GetResults().build_kernel_duration.count(), 0);
}

TEST_F(ParallelBBPProfilerTest, GetResultsAfterComputeDigits) {
  this->bbp_->Initialize();
  this->bbp_->ComputeDigits(24, 516);
  EXPECT_GT(this->bbp_->GetResults().compute_digits_duration.count(), 0);
  EXPECT_GT(this->bbp_->GetResults().read_buffer_duration.count(), 0);
  EXPECT_GT(this->bbp_->GetResults().enqueue_nd_range_duration.count(), 0);
  EXPECT_GT(this->bbp_->GetResults().digits_per_second, 0.0f);
  EXPECT_GT(this->bbp_->GetResults().bandwidth, 0.0f);
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
  } catch (const clpp::Error &error) {
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

  EXPECT_NEAR(ocl_duration, cpp_duration, 1000);  // Millisecond precision
}
