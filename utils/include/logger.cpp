#include "logger.h"

mila::Logger::~Logger() {

}

std::unique_ptr<mila::Logger> mila::LoggerFactory::MakePrintf() const {
  return std::unique_ptr<mila::Logger>(new PrintfLogger());
}

mila::PrintfLogger::PrintfLogger() : level_(LEVELS::INFO) {

}
mila::PrintfLogger::~PrintfLogger() {

}
void mila::PrintfLogger::SetLevel(mila::LEVELS level) {
  level_ = level;
}
// There is no easy way to forward variadic arguments to avoid duplicated code
void mila::PrintfLogger::Critical(const char *message, ...) const {
  if (level_ <= LEVELS::CRITICAL) {
    printf("CRITICAL ");
    va_list args;
    va_start(args, message);
    vprintf(message, args);
    va_end(args);
    printf("\n");
  }
}
void mila::PrintfLogger::Error(const char *message, ...) const {
  if (level_ <= LEVELS::ERROR) {
    printf("ERROR    ");
    va_list args;
    va_start(args, message);
    vprintf(message, args);
    va_end(args);
    printf("\n");
  }
}
void mila::PrintfLogger::Warning(const char *message, ...) const {
  if (level_ <= LEVELS::WARNING) {
    printf("WARNING  ");
    va_list args;
    va_start(args, message);
    vprintf(message, args);
    va_end(args);
    printf("\n");
  }
}
void mila::PrintfLogger::Info(const char *message, ...) const {
  if (level_ <= LEVELS::INFO) {
    printf("INFO     ");
    va_list args;
    va_start(args, message);
    vprintf(message, args);
    va_end(args);
    printf("\n");
  }
}
void mila::PrintfLogger::Debug(const char *message, ...) const {
  if (level_ <= LEVELS::DEBUG) {
    printf("DEBUG    ");
    va_list args;
    va_start(args, message);
    vprintf(message, args);
    va_end(args);
    printf("\n");
  }
}