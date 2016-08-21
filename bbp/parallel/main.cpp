#include <memory>

#include "logger.h"
#include "ocl_app.h"
#include "version.h"

int main(int argc, char **argv) {
  auto logger = std::shared_ptr<mila::Logger>(mila::LoggerFactory().MakePrintf());
  logger->Info("Version: %s", mila::version::GetVersion().c_str());
  auto ocl_app = mila::OpenCLApplicationFactory().MakeGeneric(0, 0, logger);
  logger->Info("Platform name: %s", ocl_app->GetPlatformName().c_str());
  logger->Info("Device name: %s", ocl_app->GetDeviceName().c_str());

  return 0;
}

