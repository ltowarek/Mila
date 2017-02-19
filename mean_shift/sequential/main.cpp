#include <memory>

#include "mean_shift_sequential_app.hpp"
#include "version.hpp"

int main(int argc, char **argv) {
  auto logger = std::shared_ptr<mila::Logger>(mila::LoggerFactory().MakePrintf());
  logger->Info("Version: %s", mila::version::GetVersion().c_str());
  mila::SequentialMeanShiftApp(logger).Run(argc, argv);

  return 0;
}
