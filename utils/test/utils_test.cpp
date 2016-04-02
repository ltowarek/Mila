#include "gtest/gtest.h"
#include "utils.h"

TEST(UtilsTest, Mean) {
  std::vector<float> values = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f};
  EXPECT_EQ(mila::utils::Mean(values), 5.5f);
  values = {10000, 10000, 10000, 10000, 10000};
  EXPECT_EQ(mila::utils::Mean(values), 10000);
  values = {2, 4, 4, 4, 5, 5, 7, 9};
  EXPECT_EQ(mila::utils::Mean(values), 5);
}

TEST(UtilsTest, Variance) {
  std::vector<float> values = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f};
  EXPECT_NEAR(mila::utils::Variance(values), 9.16667f, 1e-5);
  values = {10000, 10000, 10000, 10000, 10000};
  EXPECT_EQ(mila::utils::Variance(values), 0);
  values = {2, 4, 4, 4, 5, 5, 7, 9};
  EXPECT_NEAR(mila::utils::Variance(values), 4.57143f, 1e-5);
}

TEST(UtilsTest, StandardDeviation) {
  std::vector<float> values = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f};
  EXPECT_NEAR(mila::utils::StandardDeviation(values), 3.02765f, 1e-5);
  values = {10000, 10000, 10000, 10000, 10000};
  EXPECT_EQ(mila::utils::StandardDeviation(values), 0);
  values = {2, 4, 4, 4, 5, 5, 7, 9};
  EXPECT_NEAR(mila::utils::StandardDeviation(values), 2.13809f, 1e-5);
}

TEST(UtilsTest, CoefficientOfVariation) {
  std::vector<float> values = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f};
  EXPECT_NEAR(mila::utils::CoefficientOfVariation(values), 0.55048f, 1e-5);
  values = {10000, 10000, 10000, 10000, 10000};
  EXPECT_EQ(mila::utils::CoefficientOfVariation(values), 0);
  values = {2, 4, 4, 4, 5, 5, 7, 9};
  EXPECT_NEAR(mila::utils::CoefficientOfVariation(values), 0.42761f, 1e-5);
}

TEST(UtilsTest, Median) {
  std::vector<float> values = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f};
  EXPECT_NEAR(mila::utils::Median(values), 5.5f, 1e-5);
  values = {10000, 10000, 10000, 10000, 10000};
  EXPECT_EQ(mila::utils::Median(values), 10000);
  values = {2, 4, 4, 4, 5, 5, 7, 9};
  EXPECT_NEAR(mila::utils::Median(values), 4.5f, 1e-5);
  values = {1, 2, 3, 4, 5};
  EXPECT_NEAR(mila::utils::Median(values), 3.0f, 1e-5);
}
