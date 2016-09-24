#ifndef MILA_LOGGER_H
#define MILA_LOGGER_H

#include <algorithm>
#include <cstdio>
#include <cstdarg>
#include <memory>
#include <vector>

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

class LoggerFactory {
public:
  std::unique_ptr<Logger> MakePrintf() const;
};

class PrintfLogger: public Logger {
 public:
  PrintfLogger();
  virtual ~PrintfLogger();
  virtual void SetLevel(LEVELS level) override;
  virtual void Critical(const char *message, ...) const override;
  virtual void Error(const char *message, ...) const override;
  virtual void Warning(const char *message, ...) const override;
  virtual void Info(const char *message, ...) const override;
  virtual void Debug(const char *message, ...) const override;
 private:
  LEVELS level_;
};

extern std::vector<std::string> logger_spy_messages;

class LoggerSpy : public Logger {
 public:
  LoggerSpy();
  virtual ~LoggerSpy();
  virtual void SetLevel(LEVELS level) override;
  virtual void Critical(const char *message, ...) const override;
  virtual void Error(const char *message, ...) const override;
  virtual void Warning(const char *message, ...) const override;
  virtual void Info(const char *message, ...) const override;
  virtual void Debug(const char *message, ...) const override;
};

bool ContainsStr(const std::vector<std::string> &v, const std::string str);

}  // mila
#endif //MILA_LOGGER_H
