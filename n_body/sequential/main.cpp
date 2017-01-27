#include <memory>

#include "n_body_sequential_app.h"
#include "version.h"

int main(int argc, char **argv) {
  auto logger = std::shared_ptr<mila::Logger>(mila::LoggerFactory().MakePrintf());
  logger->Info("Version: %s", mila::version::GetVersion().c_str());
  mila::SequentialNBodyApp(logger).Run(argc, argv);

  return 0;
}

