#include "gtest/gtest.h"
#include "bbp_factories.h"

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

template<>
std::unique_ptr<mila::BBP> CreateBBP<mila::SequentialBBP>() {
  return mila::BBPFactory().MakeSequential(nullptr);
}

template<>
std::unique_ptr<mila::BBP> CreateBBP<mila::SequentialBBPProfiler>() {
  return mila::BBPFactory().MakeSequentialProfiler(nullptr);
}

template<typename T>
class BBPTest : public testing::Test {
 protected:
  BBPTest() : bbp_(std::move(CreateBBP<T>())) {}
  std::unique_ptr<mila::BBP> bbp_;
};

typedef testing::Types<mila::ParallelBBP,
                       mila::GenericBBPProfiler,
                       mila::ParallelBBPProfiler,
                       mila::SequentialBBP,
                       mila::SequentialBBPProfiler> BBPImplementations;

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
