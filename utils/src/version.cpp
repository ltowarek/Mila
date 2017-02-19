#include <string>
#include <sstream>
#include "version.hpp"

std::string mila::GetVersion() {
  std::stringstream ss;
  ss << MILA_VERSION_MAJOR << "." << MILA_VERSION_MINOR << "." << MILA_VERSION_PATCH;
  return ss.str();
}
