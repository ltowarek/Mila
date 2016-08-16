#include "logger.h"

mila::Logger::~Logger() {

}

mila::PrintfLogger::PrintfLogger() {
  level_ = LEVELS::WARNING;
}
mila::PrintfLogger::~PrintfLogger() {

}
void mila::PrintfLogger::SetLevel(mila::LEVELS level) {
  level_ = level;
}
// There is no easy way to forward variadic arguments to avoid duplicated code
void mila::PrintfLogger::Critical(const char *message, ...) const {
  if (level_ <= LEVELS::CRITICAL) {
    printf("Critical: ");
    va_list args;
    va_start(args, message);
    vprintf(message, args);
    va_end(args);
    printf("\n");
  }
}
void mila::PrintfLogger::Error(const char *message, ...) const {
  if (level_ <= LEVELS::ERROR) {
    printf("Error: ");
    va_list args;
    va_start(args, message);
    vprintf(message, args);
    va_end(args);
    printf("\n");
  }
}
void mila::PrintfLogger::Warning(const char *message, ...) const {
  if (level_ <= LEVELS::WARNING) {
    printf("Warning: ");
    va_list args;
    va_start(args, message);
    vprintf(message, args);
    va_end(args);
    printf("\n");
  }
}
void mila::PrintfLogger::Info(const char *message, ...) const {
  if (level_ <= LEVELS::INFO) {
    printf("Info: ");
    va_list args;
    va_start(args, message);
    vprintf(message, args);
    va_end(args);
    printf("\n");
  }
}
void mila::PrintfLogger::Debug(const char *message, ...) const {
  if (level_ <= LEVELS::DEBUG) {
    printf("Debug: ");
    va_list args;
    va_start(args, message);
    vprintf(message, args);
    va_end(args);
    printf("\n");
  }
}
