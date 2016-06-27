#include <string>
#include <sstream>
#include "version.h"

std::string mila::version::PrintVersion() {
  std::stringstream ss;
  ss << "Mila version: " << MILA_VERSION_MAJOR << "." << MILA_VERSION_MINOR << "." << MILA_VERSION_PATCH;
  return ss.str();
}

