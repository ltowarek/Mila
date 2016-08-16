#include "logger.h"

mila::Logger::~Logger() {

}

mila::PrintfLogger::PrintfLogger() {

}
mila::PrintfLogger::~PrintfLogger() {

}
// There is no easy way to forward variadic arguments to avoid duplicated code
void mila::PrintfLogger::Critical(const char *message, ...) const {
  printf("Critical: ");
  va_list args;
  va_start(args, message);
  vprintf(message, args);
  va_end(args);
  printf("\n");
}
void mila::PrintfLogger::Error(const char *message, ...) const {
  printf("Error: ");
  va_list args;
  va_start(args, message);
  vprintf(message, args);
  va_end(args);
  printf("\n");
}
void mila::PrintfLogger::Warning(const char *message, ...) const {
  printf("Warning: ");
  va_list args;
  va_start(args, message);
  vprintf(message, args);
  va_end(args);
  printf("\n");
}
void mila::PrintfLogger::Info(const char *message, ...) const {
  printf("Info: ");
  va_list args;
  va_start(args, message);
  vprintf(message, args);
  va_end(args);
  printf("\n");
}
void mila::PrintfLogger::Debug(const char *message, ...) const {
  printf("Debug: ");
  va_list args;
  va_start(args, message);
  vprintf(message, args);
  va_end(args);
  printf("\n");
}
