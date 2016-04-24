#include "gtest/gtest.h"
#include "n_body_sequential.h"

TEST(NBodySequentialTest, DefaultConstructor) {
  mila::nbody::sequential::NBodySequential n_body;
  EXPECT_EQ(n_body.precision(), 1e-5f);
}

TEST(NBodySequentialTest, PrecisionConstructor) {
  mila::nbody::sequential::NBodySequential n_body(1e-7);
  EXPECT_EQ(n_body.precision(), 1e-7f);
}
