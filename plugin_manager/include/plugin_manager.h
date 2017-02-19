#ifndef MILA_PLUGIN_MANAGER_H
#define MILA_PLUGIN_MANAGER_H

#include "plugin.h"
#include "logger.h"

#include "bbp_sequential_app.h"
#include "bbp_parallel_app.h"
#include "mean_shift_sequential_app.h"
#include "mean_shift_parallel_app.h"
#include "mean_shift_image_processing_app.h"
#include "n_body_sequential_app.h"
#include "n_body_parallel_app.h"
#include "n_body_interactive_view_app.h"

namespace mila {
class PluginManager {
 public:
  static std::unique_ptr<mila::Plugin> Create(const std::string &name, const std::shared_ptr<mila::Logger> logger);
};
}  // mila

#endif //MILA_PLUGIN_MANAGER_H
