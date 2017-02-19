#include "plugin_manager.h"

std::unique_ptr<mila::Plugin> mila::PluginManager::Create(const std::string &name, const std::shared_ptr<mila::Logger> logger) {
  auto plugin = std::unique_ptr<mila::Plugin>();

  if (name.compare("bbp_sequential") == 0) {
    plugin = std::unique_ptr<mila::Plugin>(new mila::SequentialBBPApp(logger));
  } else if (name.compare("bbp_parallel") == 0) {
    plugin = std::unique_ptr<mila::Plugin>(new mila::ParallelBBPApp(logger));
  } else if (name.compare("mean_shift_sequential") == 0) {
    plugin = std::unique_ptr<mila::Plugin>(new mila::SequentialMeanShiftApp(logger));
  } else if (name.compare("mean_shift_parallel") == 0) {
    plugin = std::unique_ptr<mila::Plugin>(new mila::ParallelMeanShiftApp(logger));
  } else if (name.compare("mean_shift_sequential_image_processing") == 0) {
    plugin = std::unique_ptr<mila::Plugin>(new mila::SequentialMeanShiftImageProcessingApp(logger));
  } else if (name.compare("mean_shift_parallel_image_processing") == 0) {
    plugin = std::unique_ptr<mila::Plugin>(new mila::ParallelMeanShiftImageProcessingApp(logger));
  } else if (name.compare("n_body_sequential") == 0) {
    plugin = std::unique_ptr<mila::Plugin>(new mila::SequentialNBodyApp(logger));
  } else if (name.compare("n_body_parallel") == 0) {
    plugin = std::unique_ptr<mila::Plugin>(new mila::ParallelNBodyApp(logger));
  } else if (name.compare("n_body_sequential_interactive_view") == 0) {
    plugin = std::unique_ptr<mila::Plugin>(new mila::SequentialNBodyInteractiveViewApp(logger));
  } else if (name.compare("n_body_parallel_interactive_view") == 0) {
    plugin = std::unique_ptr<mila::Plugin>(new mila::ParallelNBodyInteractiveViewApp(logger));
  }

  return plugin;
}
