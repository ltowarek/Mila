#include "gtest/gtest.h"
#include "utils.hpp"

TEST(UtilsTest, Mean) {
  std::vector<float> values = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f};
  EXPECT_EQ(mila::Mean(values), 5.5f);
  values = {10000, 10000, 10000, 10000, 10000};
  EXPECT_EQ(mila::Mean(values), 10000);
  values = {2, 4, 4, 4, 5, 5, 7, 9};
  EXPECT_EQ(mila::Mean(values), 5);
}

TEST(UtilsTest, Variance) {
  std::vector<float> values = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f};
  EXPECT_NEAR(mila::Variance(values), 9.16667f, 1e-5);
  values = {10000, 10000, 10000, 10000, 10000};
  EXPECT_EQ(mila::Variance(values), 0);
  values = {2, 4, 4, 4, 5, 5, 7, 9};
  EXPECT_NEAR(mila::Variance(values), 4.57143f, 1e-5);
}

TEST(UtilsTest, StandardDeviation) {
  std::vector<float> values = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f};
  EXPECT_NEAR(mila::StandardDeviation(values), 3.02765f, 1e-5);
  values = {10000, 10000, 10000, 10000, 10000};
  EXPECT_EQ(mila::StandardDeviation(values), 0);
  values = {2, 4, 4, 4, 5, 5, 7, 9};
  EXPECT_NEAR(mila::StandardDeviation(values), 2.13809f, 1e-5);
}

TEST(UtilsTest, CoefficientOfVariation) {
  std::vector<float> values = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f};
  EXPECT_NEAR(mila::CoefficientOfVariation(values), 0.55048f, 1e-5);
  values = {10000, 10000, 10000, 10000, 10000};
  EXPECT_EQ(mila::CoefficientOfVariation(values), 0);
  values = {2, 4, 4, 4, 5, 5, 7, 9};
  EXPECT_NEAR(mila::CoefficientOfVariation(values), 0.42761f, 1e-5);
}

TEST(UtilsTest, Median) {
  std::vector<float> values = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f};
  EXPECT_NEAR(mila::Median(values), 5.5f, 1e-5);
  values = {10000, 10000, 10000, 10000, 10000};
  EXPECT_EQ(mila::Median(values), 10000);
  values = {2, 4, 4, 4, 5, 5, 7, 9};
  EXPECT_NEAR(mila::Median(values), 4.5f, 1e-5);
  values = {1, 2, 3, 4, 5};
  EXPECT_NEAR(mila::Median(values), 3.0f, 1e-5);
}

TEST(UtilsTest, Sum) {
  std::vector<float> values = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f};
  EXPECT_NEAR(mila::Sum(values), 55.0f, 1e-5);
}

TEST(UtilsTest, ReadFile) {
  // TODO: Replace real file with mocked data
  EXPECT_STREQ(mila::ReadFile("test.txt").c_str(), "Test file content");
  EXPECT_STREQ(mila::ReadFile("fake_file").c_str(), "");
}

TEST(UtilsTest, GetDigitsPerSecond) {
  auto one_second = std::chrono::seconds(1);
  EXPECT_NEAR(mila::GetValuePerSecond(100, one_second), 100.0f, 1e-5);
  auto one_microsecond = std::chrono::duration<float, std::micro>(1.0f);
  EXPECT_NEAR(mila::GetValuePerSecond(100, one_microsecond), 100000000.0f, 1e05);
  EXPECT_NEAR(mila::GetValuePerSecond(1, one_microsecond), 1000000.0f, 1e-5);
  auto sample_duration = std::chrono::duration<float>(0.243811563f);
  EXPECT_NEAR(mila::GetValuePerSecond(540, sample_duration), 2214.825225496f, 1e-5f);
}

TEST(UtilsTest, ExtractTimeCountFromVector) {
  const auto input = std::vector<std::chrono::microseconds>{
      std::chrono::microseconds(1),
      std::chrono::microseconds(2),
      std::chrono::microseconds(3)
  };
  const auto expected = std::vector<float>{1.0f, 2.0f, 3.0f};
  EXPECT_EQ(mila::ExtractTimeCountFromVector(input), expected);
}
