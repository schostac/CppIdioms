#pragma once

#include <string>
#include <memory>

class Logger {
public:
  Logger();
  ~Logger();

  Logger(const Logger&) = delete;
  Logger(Logger&&);

  Logger& operator=(const Logger&) = delete;
  Logger& operator=(Logger&&);

  void log(const std::string&);
  
private:
  class LoggerImpl;
  std::unique_ptr<LoggerImpl> impl;
};