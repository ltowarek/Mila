#include "gtest/gtest.h"
#include "mean_shift_utils.h"

TEST(MeanShiftUtilsPointTest, InitializeWithSingleValue) {
  mila::Point point = {0.0f};
  EXPECT_EQ(point.x, 0.0f);
  EXPECT_EQ(point.y, 0.0f);
  EXPECT_EQ(point.z, 0.0f);
  EXPECT_EQ(point.w, 0.0f);
}

TEST(MeanShiftUtilsPointTest, InitializeWithMultipleValues) {
  mila::Point point = {1.0f, 2.0f, 3.0f, 4.0f};
  EXPECT_EQ(point.x, 1.0f);
  EXPECT_EQ(point.y, 2.0f);
  EXPECT_EQ(point.z, 3.0f);
  EXPECT_EQ(point.w, 4.0f);
}

TEST(MeanShiftUtilsPointTest, ConvertVectorToPoints) {
  std::vector<uint8_t> data = {1, 2, 3, 4, 5, 6, 7, 8};
  std::vector<mila::Point> expected_output = {{1.0f, 2.0f, 3.0f, 4.0f},
                                              {5.0f, 6.0f, 7.0f, 8.0f}
  };

  std::vector<mila::Point> output = mila::ConvertVectorToPoints(data);

  for (size_t i = 0; i < expected_output.size(); ++i) {
    EXPECT_EQ(output[i].x, expected_output[i].x);
    EXPECT_EQ(output[i].y, expected_output[i].y);
    EXPECT_EQ(output[i].z, expected_output[i].z);
    EXPECT_EQ(output[i].w, expected_output[i].w);
  }
}

TEST(MeanShiftUtilsPointTest, ConvertVectorToPointsIllegal) {
  std::vector<uint8_t> data = {1, 2, 3};

  try {
    mila::ConvertVectorToPoints(data);
  } catch (const std::runtime_error &error) {
    EXPECT_STREQ(error.what(), "Vector size is not divisible by 4");
  }
}

TEST(MeanShiftUtilsPointTest, ConvertPointsToVector) {
  std::vector<mila::Point> data = {{1.0f, 2.0f, 3.0f, 4.0f},
                                   {5.0f, 6.0f, 7.0f, 8.0f}
  };
  std::vector<uint8_t> expected_output = {1, 2, 3, 4, 5, 6, 7, 8};

  std::vector<uint8_t> output = mila::ConvertPointsToVector(data);

  for (size_t i = 0; i < expected_output.size(); ++i) {
    EXPECT_EQ(output[i], expected_output[i]);
  }
}

TEST(MeanShiftUtilsImageTest, Read) {
  mila::Image image("test_image.png");
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

TEST(MeanShiftUtilsImageTest, ReadIllegal) {
  mila::Image image;
  try {
    image.Read();
  } catch (const std::runtime_error &error) {
    EXPECT_STREQ(error.what(), "Failed to decode an image: failed to open file for reading");
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

  mila::Image output_image("test_image_output.png");
  output_image.Write(data, 5, 1);
  std::vector<uint8_t> output = output_image.Read();

  mila::Image reference_image("test_image.png");
  std::vector<uint8_t> expected_output = reference_image.Read();

  for (size_t i = 0; i < expected_output.size(); ++i) {
    EXPECT_EQ(output[i], expected_output[i]);
  }
}

TEST(MeanShiftUtilsImageTest, WriteIllegal) {
  mila::Image image;
  try {
    image.Write({}, 0, 0);
  } catch (const std::runtime_error &error) {
    EXPECT_STREQ(error.what(), "Failed to encode an image: failed to open file for writing");
  }
}
