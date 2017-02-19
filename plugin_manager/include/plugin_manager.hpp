#ifndef MILA_PLUGIN_MANAGER_H
#define MILA_PLUGIN_MANAGER_H

#include "plugin.hpp"
#include "logger.hpp"

#include "bbp_sequential_app.hpp"
#include "bbp_parallel_app.hpp"
#include "mean_shift_sequential_app.hpp"
#include "mean_shift_parallel_app.hpp"
#include "mean_shift_image_processing_app.hpp"
#include "n_body_sequential_app.hpp"
#include "n_body_parallel_app.hpp"
#include "n_body_interactive_view_app.hpp"

namespace mila {
class PluginManager {
 public:
  static std::unique_ptr<mila::Plugin> Create(const std::string &name, const std::shared_ptr<mila::Logger> logger);
};
}  // mila
#endif //MILA_PLUGIN_MANAGER_H
