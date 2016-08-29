#include "bbp_sequential_app.h"

mila::SequentialBBPApp::SequentialBBPApp(const std::shared_ptr<mila::Logger> logger): logger_(logger) {

}
mila::SequentialBBPApp::~SequentialBBPApp() {

}
void mila::SequentialBBPApp::Run(int argc, char **argv) const {
  auto config = ParseCommandLine(argc, argv);
}
mila::SequentialBBPApp::Parameters mila::SequentialBBPApp::ParseCommandLine(int argc, char **argv) const {
  if (argc < 4) {
    throw std::runtime_error("Wrong number of parameters: " + std::to_string(argc));
  }
  auto config = Parameters{0};
  config.number_of_digits = static_cast<size_t>(atoi(argv[1]));
  config.starting_position = static_cast<size_t>(atoi(argv[2]));
  config.number_of_iterations = static_cast<size_t>(atoi(argv[3]));
  return config;
}
