#include "gtest/gtest.h"
#include "bbp_utils.h"

TEST(BBPUtilsTest, ConvertFractionToHex) {
  EXPECT_EQ(mila::bbp::utils::ConvertFractionToHex(0.141587316989899f, 6), "243F11");
  EXPECT_EQ(mila::bbp::utils::ConvertFractionToHex(0.265479207038879f, 6), "43F672");
  EXPECT_EQ(mila::bbp::utils::ConvertFractionToHex(0.7426779270172f, 6), "BE2024");
  EXPECT_EQ(mila::bbp::utils::ConvertFractionToHex(0.0f, 0), "");
  EXPECT_EQ(mila::bbp::utils::ConvertFractionToHex(1.0f, 1), "0");
  EXPECT_EQ(mila::bbp::utils::ConvertFractionToHex(1.0f, 2), "00");
  EXPECT_EQ(mila::bbp::utils::ConvertFractionToHex(2.0f, 1), "0");
  EXPECT_EQ(mila::bbp::utils::ConvertFractionToHex(1.1f, 1), "1");
  EXPECT_EQ(mila::bbp::utils::ConvertFractionToHex(1.2f, 1), "3");
  EXPECT_EQ(mila::bbp::utils::ConvertFractionToHex(1.3f, 1), "4");
  EXPECT_EQ(mila::bbp::utils::ConvertFractionToHex(1.4f, 1), "6");
  EXPECT_EQ(mila::bbp::utils::ConvertFractionToHex(1.5f, 1), "8");
  EXPECT_EQ(mila::bbp::utils::ConvertFractionToHex(1.6f, 1), "9");
  EXPECT_EQ(mila::bbp::utils::ConvertFractionToHex(1.7f, 1), "B");
  EXPECT_EQ(mila::bbp::utils::ConvertFractionToHex(1.8f, 1), "C");
  EXPECT_EQ(mila::bbp::utils::ConvertFractionToHex(1.9f, 1), "E");
}

TEST(BBPUtilsTest, ConvertFractionsToHex) {
  std::vector<float> fractions = {0.141587316989899f, 0.265479207038879f};
  ASSERT_EQ(mila::bbp::utils::ConvertFractionsToHex(fractions, 6).size(), fractions.size());
  EXPECT_EQ(mila::bbp::utils::ConvertFractionsToHex(fractions, 6)[0], "243F11");
  EXPECT_EQ(mila::bbp::utils::ConvertFractionsToHex(fractions, 6)[1], "43F672");
}

TEST(BBPUtilsTest, Mean) {
  std::vector<float> values = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f};
  EXPECT_EQ(mila::bbp::utils::Mean(values), 5.5f);
  values = {10000, 10000, 10000, 10000, 10000};
  EXPECT_EQ(mila::bbp::utils::Mean(values), 10000);
  values = {2, 4, 4, 4, 5, 5, 7, 9};
  EXPECT_EQ(mila::bbp::utils::Mean(values), 5);
}

TEST(BBPUtilsTest, Variance) {
  std::vector<float> values = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f};
  EXPECT_NEAR(mila::bbp::utils::Variance(values), 9.16667f, 1e-5);
  values = {10000, 10000, 10000, 10000, 10000};
  EXPECT_EQ(mila::bbp::utils::Variance(values), 0);
  values = {2, 4, 4, 4, 5, 5, 7, 9};
  EXPECT_NEAR(mila::bbp::utils::Variance(values), 4.57143f, 1e-5);
}

TEST(BBPUtilsTest, StandardDeviation) {
  std::vector<float> values = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f};
  EXPECT_NEAR(mila::bbp::utils::StandardDeviation(values), 3.02765f, 1e-5);
  values = {10000, 10000, 10000, 10000, 10000};
  EXPECT_EQ(mila::bbp::utils::StandardDeviation(values), 0);
  values = {2, 4, 4, 4, 5, 5, 7, 9};
  EXPECT_NEAR(mila::bbp::utils::StandardDeviation(values), 2.13809f, 1e-5);
}

TEST(BBPUtilsTest, CoefficientOfVariation) {
  std::vector<float> values = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f};
  EXPECT_NEAR(mila::bbp::utils::CoefficientOfVariation(values), 0.55048f, 1e-5);
  values = {10000, 10000, 10000, 10000, 10000};
  EXPECT_EQ(mila::bbp::utils::CoefficientOfVariation(values), 0);
  values = {2, 4, 4, 4, 5, 5, 7, 9};
  EXPECT_NEAR(mila::bbp::utils::CoefficientOfVariation(values), 0.42761f, 1e-5);
}

TEST(BBPUtilsTest, Median) {
  std::vector<float> values = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f};
  EXPECT_NEAR(mila::bbp::utils::Median(values), 5.5f, 1e-5);
  values = {10000, 10000, 10000, 10000, 10000};
  EXPECT_EQ(mila::bbp::utils::Median(values), 10000);
  values = {2, 4, 4, 4, 5, 5, 7, 9};
  EXPECT_NEAR(mila::bbp::utils::Median(values), 4.5f, 1e-5);
  values = {1, 2, 3, 4, 5};
  EXPECT_NEAR(mila::bbp::utils::Median(values), 3.0f, 1e-5);
}

TEST(BBPUtilsTest, ReadFile) {
  // TODO: Replace real file with mocked data
  EXPECT_STREQ(mila::bbp::utils::ReadFile("test.txt").c_str(), "Test file content");
  EXPECT_STREQ(mila::bbp::utils::ReadFile("fake_file").c_str(), "");
}
