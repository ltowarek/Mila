#ifndef MILA_PLUGIN_H
#define MILA_PLUGIN_H

namespace mila {
class Plugin {
 public:
  virtual ~Plugin() = 0;
  virtual void Run(int argc, char **argv) const = 0;
};
}  // mila
#endif //MILA_PLUGIN_H
