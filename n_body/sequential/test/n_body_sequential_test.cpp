#include "gtest/gtest.h"
#include "n_body_sequential.h"

TEST(NBodyVector2DTest, InitializeWithSingleValue) {
  mila::nbody::sequential::Vector2D vector2D = {0.0f};
  EXPECT_EQ(vector2D.x, 0.0f);
  EXPECT_EQ(vector2D.y, 0.0f);
}

TEST(NBodyVector2DTest, InitializeWithMultipleValues) {
  mila::nbody::sequential::Vector2D vector2D = {1.0f, 2.0f};
  EXPECT_EQ(vector2D.x, 1.0f);
  EXPECT_EQ(vector2D.y, 2.0f);
}

TEST(NBodyVector2DTest, DistanceZero) {
  mila::nbody::sequential::Vector2D vector1 = {0.0f};
  mila::nbody::sequential::Vector2D vector2 = {0.0f};
  EXPECT_EQ(mila::nbody::sequential::Distance(vector1, vector2), 0.0f);
}

TEST(NBodyVector2DTest, DistanceComplex) {
  mila::nbody::sequential::Vector2D vector1 = {3.0f, 2.0f};
  mila::nbody::sequential::Vector2D vector2 = {5.0f, -1.0f};
  EXPECT_NEAR(mila::nbody::sequential::Distance(vector1, vector2), 3.60555f, 1e-5f);
}

TEST(NBodySequentialTest, DefaultConstructor) {
  mila::nbody::sequential::NBodySequential n_body;
  EXPECT_EQ(n_body.precision(), 1e-5f);
}

TEST(NBodySequentialTest, PrecisionConstructor) {
  mila::nbody::sequential::NBodySequential n_body(1e-7);
  EXPECT_EQ(n_body.precision(), 1e-7f);
}

TEST(NBodySequentialTest, GenerateParticles) {
  mila::nbody::sequential::NBodySequential n_body(1e-7);
  EXPECT_EQ(n_body.precision(), 1e-7f);
}
