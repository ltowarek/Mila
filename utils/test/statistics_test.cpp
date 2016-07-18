#include "gtest/gtest.h"
#include "statistics.h"

TEST(OpenCLStatisticsTest, GetOpenCLStatisticsAsString) {
  auto statistics = mila::statistics::OpenCLStatistics();
  EXPECT_STREQ("Build kernel: 0 us, Read buffer: 0 us, Enqueue ND range: 0 us", statistics.GetOpenCLStatisticsAsString().c_str());
}

TEST(OpenCLStatisticsTest, GetBuildKernelAsString) {
  auto statistics = mila::statistics::OpenCLStatistics();
  EXPECT_STREQ("Build kernel: 0 us", statistics.GetBuildKernelAsString().c_str());
}

TEST(OpenCLStatisticsTest, GetBuildKernelAsMicroseconds) {
  auto statistics = mila::statistics::OpenCLStatistics();
  EXPECT_EQ(std::chrono::microseconds(0).count(), statistics.GetBuildKernelAsMicroseconds());
}

TEST(OpenCLStatisticsTest, SetBuildKernelAsMicroseconds) {
  auto statistics = mila::statistics::OpenCLStatistics();
  statistics.SetBuildKernelAsMicroseconds(1000);
  EXPECT_EQ(std::chrono::microseconds(1000).count(), statistics.GetBuildKernelAsMicroseconds());
}

TEST(OpenCLStatisticsTest, GetReadBufferAsString) {
  auto statistics = mila::statistics::OpenCLStatistics();
  EXPECT_STREQ("Read buffer: 0 us", statistics.GetReadBufferAsString().c_str());
}

TEST(OpenCLStatisticsTest, GetReadBufferAsMicroseconds) {
  auto statistics = mila::statistics::OpenCLStatistics();
  EXPECT_EQ(std::chrono::microseconds(0).count(), statistics.GetReadBufferAsMicroseconds());
}

TEST(OpenCLStatisticsTest, SetReadBufferAsMicroseconds) {
  auto statistics = mila::statistics::OpenCLStatistics();
  statistics.SetReadBufferAsMicroseconds(1000);
  EXPECT_EQ(std::chrono::microseconds(1000).count(), statistics.GetReadBufferAsMicroseconds());
}

TEST(OpenCLStatisticsTest, GetEnqueueNDRangeAsString) {
  auto statistics = mila::statistics::OpenCLStatistics();
  EXPECT_STREQ("Enqueue ND range: 0 us", statistics.GetEnqueueNDRangeAsString().c_str());
}

TEST(OpenCLStatisticsTest, GetEnqueueNDRangeAsMicroseconds) {
  auto statistics = mila::statistics::OpenCLStatistics();
  EXPECT_EQ(std::chrono::microseconds(0).count(), statistics.GetEnqueueNDRangeAsMicroseconds());
}

TEST(OpenCLStatisticsTest, SetEnqueueNDRangeAsMicroseconds) {
  auto statistics = mila::statistics::OpenCLStatistics();
  statistics.SetEnqueueNDRangeAsMicroseconds(1000);
  EXPECT_EQ(std::chrono::microseconds(1000).count(), statistics.GetEnqueueNDRangeAsMicroseconds());
}
