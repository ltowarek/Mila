#include <memory>

#include "logger.h"
#include "version.h"
#include "n_body_factories.h"

struct Parameters {
  std::string test_case;
};

std::string RemoveArgFromArgv(int arg, int &argc, char **argv) {
  std::string output = argv[arg];
  for (int i = arg; i < argc - 1; ++i) {
    argv[i] = argv[i + 1];
  }
  free(argv[argc]);
  argc--;
  return output;
}

Parameters ParseCommandLine(int &argc, char **argv) {
  if (argc < 2) {
    throw std::runtime_error("Wrong number of parameters: " + std::to_string(argc));
  }
  Parameters parameters;
  parameters.test_case = RemoveArgFromArgv(1, argc, argv);

  return parameters;
}

int main(int argc, char **argv) {
  auto config = ParseCommandLine(argc, argv);
  auto logger = std::shared_ptr<mila::Logger>(mila::LoggerFactory().MakePrintf());
  logger->Info("Version: %s", mila::version::GetVersion().c_str());

  auto n_body = std::unique_ptr<mila::NBodyApp>();
  n_body->Run(argc, argv);

  return 0;
}

