#include "logger.hpp"

std::vector<std::string> mila::logger_spy_messages;

bool mila::ContainsStr(const std::vector<std::string> &v, const std::string str) {
  return
      std::find_if(v.begin(), v.end(),
                   [str](const std::string &s) -> bool { return s.find(str) != std::string::npos; }) != v.end();
}

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

mila::LoggerSpy::LoggerSpy() {
  mila::logger_spy_messages.clear();
}
mila::LoggerSpy::~LoggerSpy() {

}
void mila::LoggerSpy::SetLevel(LEVELS level) {

}
void mila::LoggerSpy::Critical(const char *message, ...) const {
  va_list args1;
  va_start(args1, message);
  va_list args2;
  va_copy(args2, args1);
  auto output = std::vector<char>(1ul + vsnprintf(nullptr, 0, message, args1));
  va_end(args1);
  vsnprintf(output.data(), output.size(), message, args2);
  va_end(args2);
  logger_spy_messages.push_back("C " + std::string(output.data()));
}
void mila::LoggerSpy::Error(const char *message, ...) const {
  va_list args1;
  va_start(args1, message);
  va_list args2;
  va_copy(args2, args1);
  auto output = std::vector<char>(1ul + vsnprintf(nullptr, 0, message, args1));
  va_end(args1);
  vsnprintf(output.data(), output.size(), message, args2);
  va_end(args2);
  logger_spy_messages.push_back("E " + std::string(output.data()));
}
void mila::LoggerSpy::Warning(const char *message, ...) const {
  va_list args1;
  va_start(args1, message);
  va_list args2;
  va_copy(args2, args1);
  auto output = std::vector<char>(1ul + vsnprintf(nullptr, 0, message, args1));
  va_end(args1);
  vsnprintf(output.data(), output.size(), message, args2);
  va_end(args2);
  logger_spy_messages.push_back("W " + std::string(output.data()));
}
void mila::LoggerSpy::Info(const char *message, ...) const {
  va_list args1;
  va_start(args1, message);
  va_list args2;
  va_copy(args2, args1);
  auto output = std::vector<char>(1ul + vsnprintf(nullptr, 0, message, args1));
  va_end(args1);
  vsnprintf(output.data(), output.size(), message, args2);
  va_end(args2);
  logger_spy_messages.push_back("I " + std::string(output.data()));
}
void mila::LoggerSpy::Debug(const char *message, ...) const {
  va_list args1;
  va_start(args1, message);
  va_list args2;
  va_copy(args2, args1);
  auto output = std::vector<char>(1ul + vsnprintf(nullptr, 0, message, args1));
  va_end(args1);
  vsnprintf(output.data(), output.size(), message, args2);
  va_end(args2);
  logger_spy_messages.push_back("D " + std::string(output.data()));
}
