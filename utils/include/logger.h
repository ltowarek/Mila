#ifndef MILA_LOGGER_H
#define MILA_LOGGER_H

#include <cstdio>
#include <cstdarg>

namespace mila {
enum class LEVELS : int {DEBUG = 0, INFO = 1, WARNING = 2, ERROR = 3, CRITICAL = 4};
class Logger {
 public:
  virtual ~Logger() = 0;
  virtual void SetLevel(LEVELS level) = 0;
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
  virtual void SetLevel(LEVELS level);
  virtual void Critical(const char *message, ...) const override;
  virtual void Error(const char *message, ...) const override;
  virtual void Warning(const char *message, ...) const override;
  virtual void Info(const char *message, ...) const override;
  virtual void Debug(const char *message, ...) const override;
 private:
  LEVELS level_;
};
}  // mila
#endif //MILA_LOGGER_H
