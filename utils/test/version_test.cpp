#undef MILA_VERSION_MAJOR
#undef MILA_VERSION_MINOR
#undef MILA_VERSION_PATCH
#define MILA_VERSION_MAJOR 3
#define MILA_VERSION_MINOR 2
#define MILA_VERSION_PATCH 1

#include "gtest/gtest.h"
#include "version.h"

TEST(VersionTest, PrintVersion) {

  std::stringstream ss;
  ss << "Mila version: " << MILA_VERSION_MAJOR << "." << MILA_VERSION_MINOR << "." << MILA_VERSION_PATCH;
  std::string expected_version = ss.str();

  EXPECT_STREQ(mila::version::PrintVersion().c_str(), expected_version.c_str());
}
