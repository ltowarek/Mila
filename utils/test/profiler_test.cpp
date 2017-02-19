#include <thread>

#include "gtest/gtest.h"
#include "profiler.hpp"

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
  std::this_thread::sleep_for(std::chrono::microseconds(1));
  this->profiler_->End("Test");
  EXPECT_GT(this->profiler_->GetDuration("Test").count(), 0.0f);
}
