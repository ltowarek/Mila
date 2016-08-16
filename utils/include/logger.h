#ifndef MILA_LOGGER_H
#define MILA_LOGGER_H

#include <cstdio>
#include <cstdarg>

namespace mila {
class Logger {
 public:
  virtual ~Logger() = 0;
  virtual void Critical(const char *message, ...) const = 0;
  virtual void Error(const char *message, ...) const = 0;
  virtual void Warning(const char *message, ...) const = 0;
  virtual void Info(const char *message, ...) const = 0;
  virtual void Debug(const char *message, ...) const = 0;
};

class PrintfLogger: public Logger {
 public:
  PrintfLogger();
  virtual ~PrintfLogger();
  virtual void Critical(const char *message, ...) const override;
  virtual void Error(const char *message, ...) const override;
  virtual void Warning(const char *message, ...) const override;
  virtual void Info(const char *message, ...) const override;
  virtual void Debug(const char *message, ...) const override;
};
}  // mila
#endif //MILA_LOGGER_H
