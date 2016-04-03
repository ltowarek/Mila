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
