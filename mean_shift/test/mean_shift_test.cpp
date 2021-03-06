#include "gtest/gtest.h"
#include "mean_shift_factories.hpp"

template<typename T>
std::unique_ptr<mila::MeanShift> CreateMeanShift();

template<>
std::unique_ptr<mila::MeanShift> CreateMeanShift<mila::SequentialMeanShift>() {
  return mila::MeanShiftFactory().MakeSequential(nullptr);
}

template<>
std::unique_ptr<mila::MeanShift> CreateMeanShift<mila::SequentialMeanShiftProfiler>() {
  auto profiler = mila::ProfilerFactory().MakeChrono(nullptr);
  return mila::MeanShiftFactory().MakeSequentialProfiler(std::move(profiler), nullptr);
}

template<>
std::unique_ptr<mila::MeanShift> CreateMeanShift<mila::ParallelMeanShift>() {
  auto ocl_app = mila::OpenCLApplicationFactory().MakeGeneric(0, 0, nullptr);
  return mila::MeanShiftFactory().MakeParallel(std::move(ocl_app), nullptr);
}

template<>
std::unique_ptr<mila::MeanShift> CreateMeanShift<mila::ParallelMeanShiftProfiler>() {
  auto ocl_app = mila::OpenCLApplicationFactory().MakeGeneric(0, 0, nullptr);
  auto profiler = mila::ProfilerFactory().MakeChrono(nullptr);
  return mila::MeanShiftFactory().MakeParallelProfiler(std::move(ocl_app), std::move(profiler), nullptr);
}

template<typename T>
class MeanShiftTest : public testing::Test {
 protected:
  MeanShiftTest() : mean_shift_(std::move(CreateMeanShift<T>())) {}
  std::unique_ptr<mila::MeanShift> mean_shift_;
};

typedef testing::Types<mila::SequentialMeanShift,
                       mila::SequentialMeanShiftProfiler,
                       mila::ParallelMeanShift,
                       mila::ParallelMeanShiftProfiler> MeanShiftImplementations;

TYPED_TEST_CASE(MeanShiftTest, MeanShiftImplementations);

TYPED_TEST(MeanShiftTest, RunSimple) {
  const auto points = std::vector<mila::Point>{{0.0f, 1.0f, 0.0f, 0.0f},
                                               {2.0f, 3.0f, 0.0f, 0.0f},
                                               {10.0f, 11.0f, 0.0f, 0.0f},
                                               {12.0f, 13.0f, 0.0f, 0.0f}
  };
  const auto expected_points = std::vector<mila::Point>{{1.0f, 2.0f, 0.0f, 0.0f},
                                                        {1.0f, 2.0f, 0.0f, 0.0f},
                                                        {11.0f, 12.0f, 0.0f, 0.0f},
                                                        {11.0f, 12.0f, 0.0f, 0.0f}
  };
  const auto bandwidth = 3.0f;

  const auto output = this->mean_shift_->Run(points, bandwidth);

  for (size_t i = 0; i < points.size(); ++i) {
    EXPECT_NEAR(output[i].x, expected_points[i].x, 1e-3f);
    EXPECT_NEAR(output[i].y, expected_points[i].y, 1e-3f);
    EXPECT_NEAR(output[i].z, expected_points[i].z, 1e-3f);
    EXPECT_NEAR(output[i].w, expected_points[i].w, 1e-3f);
  }
}

TYPED_TEST(MeanShiftTest, RunComplex) {
  const auto points = std::vector<mila::Point>{{10.91079f, 8.38941f},
                                               {9.87500f, 9.90925f},
                                               {7.84812f, 10.43175f},
                                               {8.53412f, 9.55909f},
                                               {10.38317f, 9.61879f},
                                               {8.11062f, 9.77472f},
                                               {10.02119f, 9.53878f},
                                               {9.37706f, 9.70854f},
                                               {7.67017f, 9.60315f},
                                               {10.94308f, 11.76207f},
                                               {9.24731f, 10.90211f},
                                               {9.54740f, 11.36170f},
                                               {7.83334f, 10.36303f},
                                               {10.87046f, 9.21335f},
                                               {8.22851f, 10.46791f},
                                               {12.48299f, 9.42123f},
                                               {6.55723f, 11.05935f},
                                               {7.26426f, 9.98426f},
                                               {4.80172f, 7.55791f},
                                               {6.86125f, 7.83701f},
                                               {13.62724f, 10.94830f},
                                               {13.65526f, 9.92498f},
                                               {9.60609f, 10.29199f},
                                               {12.43566f, 8.81344f},
                                               {10.07207f, 9.16057f},
                                               {8.30670f, 10.44116f},
                                               {8.77244f, 10.84579f},
                                               {9.84142f, 9.84831f},
                                               {15.11169f, 12.48990f},
                                               {10.27742f, 9.85657f},
                                               {10.13481f, 8.89277f},
                                               {8.42659f, 11.30023f},
                                               {9.19120f, 9.98987f},
                                               {5.93327f, 10.21740f},
                                               {9.66606f, 10.68815f},
                                               {5.76209f, 10.12453f},
                                               {5.22427f, 9.98493f},
                                               {10.26869f, 10.31605f},
                                               {10.92377f, 10.93352f},
                                               {8.93580f, 9.18140f},
                                               {2.97821f, 3.83547f},
                                               {4.91744f, 2.67434f},
                                               {3.02456f, 4.80751f},
                                               {3.01923f, 4.04181f},
                                               {4.13152f, 2.52060f},
                                               {0.41135f, 3.65570f},
                                               {5.26644f, 5.59488f},
                                               {4.62354f, 1.37592f},
                                               {5.67864f, 2.75797f},
                                               {3.90546f, 2.14163f},
                                               {8.08535f, 2.58834f},
                                               {6.85204f, 3.61032f},
                                               {4.23085f, 3.56338f},
                                               {6.04291f, 2.35889f},
                                               {4.20077f, 2.38239f},
                                               {4.28404f, 7.05114f},
                                               {3.82064f, 4.60739f},
                                               {5.41769f, 3.43634f},
                                               {8.21146f, 3.57061f},
                                               {6.54310f, -0.15007f},
                                               {9.21725f, 2.40194f},
                                               {6.67304f, 3.30761f},
                                               {4.04304f, 4.84984f},
                                               {3.70410f, 2.25263f},
                                               {4.90816f, 3.87039f},
                                               {5.65622f, 2.24355f},
                                               {5.09180f, 3.50950f},
                                               {6.33405f, 3.51761f},
                                               {6.82059f, 3.87184f},
                                               {7.20944f, 2.85311f},
                                               {2.09972f, 2.25603f},
                                               {4.72021f, 2.62070f},
                                               {6.22199f, 4.66519f},
                                               {5.07699f, 2.35904f},
                                               {3.26303f, 0.65207f},
                                               {3.63922f, 2.05049f},
                                               {7.25011f, 2.63319f},
                                               {4.28694f, 0.74184f},
                                               {4.48918f, 1.84739f},
                                               {6.22348f, 2.22601f},
                                               {2.73268f, 4.02671f},
                                               {6.70413f, 1.24138f},
                                               {6.40673f, 6.43082f},
                                               {3.08216f, 3.60353f},
                                               {3.71943f, 5.34522f},
                                               {6.19040f, 6.92259f},
                                               {8.10188f, 4.28388f},
                                               {2.66674f, 1.25125f},
                                               {5.15625f, 2.95783f},
                                               {6.83221f, 3.00474f},
                                               {-1.52367f, 6.87094f},
                                               {-6.27805f, 5.05452f},
                                               {-4.13009f, 3.30897f},
                                               {-2.29877f, 2.52434f},
                                               {-0.18637f, 5.05983f},
                                               {-5.18408f, 5.32761f},
                                               {-5.26062f, 6.37334f},
                                               {-4.06791f, 4.56450f},
                                               {-4.85640f, 3.94371f},
                                               {-5.16902f, 7.19965f},
                                               {-2.81872f, 6.77548f},
                                               {-3.01320f, 5.30737f},
                                               {-1.84026f, 2.47302f},
                                               {-3.80602f, 3.09938f},
                                               {-1.35387f, 4.60009f},
                                               {-5.42283f, 5.54063f},
                                               {-3.57190f, 6.39053f},
                                               {-4.03798f, 4.70568f},
                                               {-1.11035f, 4.80941f},
                                               {-3.83788f, 6.02910f},
                                               {-6.55039f, 5.51181f},
                                               {-5.81634f, 7.81394f},
                                               {-4.62689f, 8.97988f},
                                               {-3.23078f, 3.29558f},
                                               {-4.33357f, 5.59336f},
                                               {-3.28290f, 6.59019f},
                                               {-7.64689f, 7.52735f},
                                               {-6.46182f, 5.62945f},
                                               {-6.36822f, 7.08386f},
                                               {-4.28476f, 3.84258f},
                                               {-2.29627f, 7.28858f},
                                               {1.10128f, 6.54880f},
                                               {-5.92794f, 8.65509f},
                                               {-3.95460f, 5.73364f},
                                               {-3.16088f, 4.26741f}
  };
  const auto expected_points = std::vector<mila::Point>{{8.63150f, 9.25489f},
                                                        {8.63150f, 9.25489f},
                                                        {8.63150f, 9.25489f},
                                                        {8.63150f, 9.25489f},
                                                        {8.63150f, 9.25489f},
                                                        {8.63150f, 9.25489f},
                                                        {8.63150f, 9.25489f},
                                                        {8.63150f, 9.25489f},
                                                        {8.63149f, 9.25489f},
                                                        {8.63150f, 9.25489f},
                                                        {8.63150f, 9.25489f},
                                                        {8.63150f, 9.25489f},
                                                        {8.63150f, 9.25489f},
                                                        {8.63150f, 9.25489f},
                                                        {8.63150f, 9.25489f},
                                                        {8.63150f, 9.25489f},
                                                        {8.63149f, 9.25489f},
                                                        {8.63149f, 9.25489f},
                                                        {5.02927f, 3.56549f},
                                                        {5.02927f, 3.56549f},
                                                        {8.63150f, 9.25489f},
                                                        {8.63150f, 9.25489f},
                                                        {8.63150f, 9.25489f},
                                                        {8.63150f, 9.25489f},
                                                        {8.63150f, 9.25489f},
                                                        {8.63150f, 9.25489f},
                                                        {8.63150f, 9.25489f},
                                                        {8.63150f, 9.25489f},
                                                        {8.63150f, 9.25489f},
                                                        {8.63150f, 9.25489f},
                                                        {8.63150f, 9.25489f},
                                                        {8.63150f, 9.25489f},
                                                        {8.63150f, 9.25489f},
                                                        {8.63149f, 9.25489f},
                                                        {8.63150f, 9.25489f},
                                                        {8.63149f, 9.25489f},
                                                        {8.63149f, 9.25489f},
                                                        {8.63150f, 9.25489f},
                                                        {8.63150f, 9.25489f},
                                                        {8.63150f, 9.25489f},
                                                        {5.02927f, 3.56549f},
                                                        {5.02927f, 3.56549f},
                                                        {5.02927f, 3.56549f},
                                                        {5.02927f, 3.56549f},
                                                        {5.02927f, 3.56549f},
                                                        {5.02927f, 3.56549f},
                                                        {5.02927f, 3.56549f},
                                                        {5.02927f, 3.56549f},
                                                        {5.02927f, 3.56549f},
                                                        {5.02927f, 3.56549f},
                                                        {5.02927f, 3.56549f},
                                                        {5.02927f, 3.56549f},
                                                        {5.02927f, 3.56549f},
                                                        {5.02927f, 3.56549f},
                                                        {5.02927f, 3.56549f},
                                                        {5.02927f, 3.56549f},
                                                        {5.02927f, 3.56549f},
                                                        {5.02927f, 3.56549f},
                                                        {5.02927f, 3.56549f},
                                                        {5.02927f, 3.56549f},
                                                        {5.02927f, 3.56549f},
                                                        {5.02927f, 3.56549f},
                                                        {5.02927f, 3.56549f},
                                                        {5.02927f, 3.56549f},
                                                        {5.02927f, 3.56549f},
                                                        {5.02927f, 3.56549f},
                                                        {5.02927f, 3.56549f},
                                                        {5.02927f, 3.56549f},
                                                        {5.02927f, 3.56549f},
                                                        {5.02927f, 3.56549f},
                                                        {5.02927f, 3.56549f},
                                                        {5.02927f, 3.56549f},
                                                        {5.02927f, 3.56549f},
                                                        {5.02927f, 3.56549f},
                                                        {5.02927f, 3.56549f},
                                                        {5.02927f, 3.56549f},
                                                        {5.02927f, 3.56549f},
                                                        {5.02927f, 3.56549f},
                                                        {5.02927f, 3.56549f},
                                                        {5.02927f, 3.56549f},
                                                        {5.02927f, 3.56549f},
                                                        {5.02927f, 3.56549f},
                                                        {5.02927f, 3.56549f},
                                                        {5.02927f, 3.56549f},
                                                        {5.02927f, 3.56549f},
                                                        {5.02927f, 3.56549f},
                                                        {5.02927f, 3.56549f},
                                                        {5.02927f, 3.56549f},
                                                        {5.02927f, 3.56549f},
                                                        {5.02927f, 3.56549f},
                                                        {-3.45216f, 5.28851f},
                                                        {-3.45216f, 5.28851f},
                                                        {-3.45216f, 5.28851f},
                                                        {-3.45216f, 5.28851f},
                                                        {5.02927f, 3.56549f},
                                                        {-3.45216f, 5.28851f},
                                                        {-3.45216f, 5.28851f},
                                                        {-3.45216f, 5.28851f},
                                                        {-3.45216f, 5.28851f},
                                                        {-3.45216f, 5.28851f},
                                                        {-3.45216f, 5.28851f},
                                                        {-3.45216f, 5.28851f},
                                                        {-3.45216f, 5.28851f},
                                                        {-3.45216f, 5.28851f},
                                                        {-3.45216f, 5.28851f},
                                                        {-3.45216f, 5.28851f},
                                                        {-3.45216f, 5.28851f},
                                                        {-3.45216f, 5.28851f},
                                                        {-3.45216f, 5.28851f},
                                                        {-3.45216f, 5.28851f},
                                                        {-3.45216f, 5.28851f},
                                                        {-3.45216f, 5.28851f},
                                                        {-3.45216f, 5.28851f},
                                                        {-3.45216f, 5.28851f},
                                                        {-3.45216f, 5.28851f},
                                                        {-3.45216f, 5.28851f},
                                                        {-3.45216f, 5.28851f},
                                                        {-3.45216f, 5.28851f},
                                                        {-3.45216f, 5.28851f},
                                                        {-3.45216f, 5.28851f},
                                                        {-3.45216f, 5.28851f},
                                                        {5.02927f, 3.56549f},
                                                        {-3.45216f, 5.28851f},
                                                        {-3.45216f, 5.28851f},
                                                        {-3.45216f, 5.28851f}
  };
  const auto bandwidth = 3.0f;

  const auto output = this->mean_shift_->Run(points, bandwidth);

  for (size_t i = 0; i < points.size(); ++i) {
    EXPECT_NEAR(output[i].x, expected_points[i].x, 1e-3f);
    EXPECT_NEAR(output[i].y, expected_points[i].y, 1e-3f);
    EXPECT_NEAR(output[i].z, expected_points[i].z, 1e-3f);
    EXPECT_NEAR(output[i].w, expected_points[i].w, 1e-3f);
  }
}

template<typename T>
std::unique_ptr<mila::MeanShiftImageProcessing> CreateMeanShiftImageProcessing();

template<>
std::unique_ptr<mila::MeanShiftImageProcessing> CreateMeanShiftImageProcessing<mila::GenericMeanShiftImageProcessing>() {
  return mila::MeanShiftImageProcessingFactory().MakeSequential(nullptr);
}

template<>
std::unique_ptr<mila::MeanShiftImageProcessing> CreateMeanShiftImageProcessing<mila::MeanShiftImageProcessingProfiler>() {
  auto profiler = mila::ProfilerFactory().MakeChrono(nullptr);
  return mila::MeanShiftImageProcessingFactory().MakeSequentialProfiler(std::move(profiler), nullptr);
}

template<typename T>
class MeanShiftImageProcessingTest : public testing::Test {
 protected:
  MeanShiftImageProcessingTest() : mean_shift_(std::move(CreateMeanShiftImageProcessing<T>())) {}
  std::unique_ptr<mila::MeanShiftImageProcessing> mean_shift_;
};

typedef testing::Types<mila::GenericMeanShiftImageProcessing, mila::MeanShiftImageProcessingProfiler>
    MeanShiftImageProcessingImplementations;

TYPED_TEST_CASE(MeanShiftImageProcessingTest, MeanShiftImageProcessingImplementations);

TYPED_TEST(MeanShiftImageProcessingTest, Run) {
  const auto input_file = std::string("test_image.png");
  const auto output_file = std::string("test_image_output.png");
  const auto reference_file = std::string("test_image_reference.png");
  const auto bandwidth = 25.0f;

  this->mean_shift_->Run(input_file, output_file, bandwidth);

  auto output_image = mila::Image(output_file);
  const auto output = std::vector<uint8_t>(output_image.Read());

  auto reference_image = mila::Image(reference_file);
  const auto reference = std::vector<uint8_t>(reference_image.Read());

  for (size_t i = 0; i < reference.size(); ++i) {
    EXPECT_EQ(output[i], reference[i]);
  }
}
