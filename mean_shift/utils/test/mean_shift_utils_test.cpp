#include "gtest/gtest.h"
#include "mean_shift_utils.h"

TEST(MeanShiftUtilsImageTest, DefaultConstructor) {
  mila::meanshift::utils::Image image;
  EXPECT_EQ(image.file_name(), "");
  EXPECT_EQ(image.width(), 0);
  EXPECT_EQ(image.height(), 0);
}

TEST(MeanShiftUtilsImageTest, Constructor) {
  mila::meanshift::utils::Image image("file.png");
  EXPECT_EQ(image.file_name(), "file.png");
  EXPECT_EQ(image.width(), 0);
  EXPECT_EQ(image.height(), 0);
}

TEST(MeanShiftUtilsImageTest, Read) {
  mila::meanshift::utils::Image image("test_image.png");
  std::vector<uint8_t> output = image.Read();
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

TEST(MeanShiftUtilsImageTest, Write) {
  std::vector<uint8_t> data = {
      255, 255, 255, 255,
      0, 0, 0, 255,
      255, 0, 0, 255,
      0, 255, 0, 255,
      0, 0, 255, 255
  };

  mila::meanshift::utils::Image output_image("test_image_output.png");
  output_image.Write(data, 5, 1);
  std::vector<uint8_t> output = output_image.Read();

  mila::meanshift::utils::Image reference_image("test_image.png");
  std::vector<uint8_t> expected_output = reference_image.Read();

  for (size_t i = 0; i < expected_output.size(); ++i) {
    EXPECT_EQ(output[i], expected_output[i]);
  }
}
