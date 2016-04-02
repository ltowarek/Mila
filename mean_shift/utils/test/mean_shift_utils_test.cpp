#include "gtest/gtest.h"
#include "mean_shift_utils.h"

TEST(MeanShiftUtilsTest, ReadPNGToVector) {
  std::vector<uint8_t> output = mila::meanshift::utils::ReadPNGToVector("test_image.png");
  std::vector<uint8_t> expected_output = {
      255, 255, 255, 255,
      0, 0, 0, 255,
      255, 0, 0, 255,
      0, 255, 0, 255,
      0, 0, 255, 255
  };
  for (size_t i = 0; i < expected_output.size(); ++i) {
    EXPECT_EQ(output[i], expected_output[i]);
  }
}

TEST(MeanShiftUtilsTest, WriteVectorToPNG) {
  std::vector<uint8_t> data = {
      255, 255, 255, 255,
      0, 0, 0, 255,
      255, 0, 0, 255,
      0, 255, 0, 255,
      0, 0, 255, 255
  };
  mila::meanshift::utils::WriteVectorToPNG("test_image_output.png", data, 5, 1);

  std::vector<uint8_t> expected_output = mila::meanshift::utils::ReadPNGToVector("test_image.png");
  std::vector<uint8_t> output = mila::meanshift::utils::ReadPNGToVector("test_image_output.png");
  for (size_t i = 0; i < expected_output.size(); ++i) {
    EXPECT_EQ(output[i], expected_output[i]);
  }
}
