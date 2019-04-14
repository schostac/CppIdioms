#include "logger/Logger.hpp"

#include <fstream>
#include <iostream>
#include <stdexcept>

namespace constants {
  static constexpr char fileName[] = "MyLogs.txt";
}

class Logger::LoggerImpl {
public:
  LoggerImpl(): file(constants::fileName) {}
  void log(const std::string & log);
private:
  std::ofstream file;
};

void Logger::LoggerImpl::log(const std::string & log) { 
  std::cout << "Logging: " << log << std::endl;
  file << log << '\n'; 
}

Logger::Logger(): impl{std::make_unique<Logger::LoggerImpl>()} {}
Logger::~Logger() = default;

Logger::Logger(Logger&&) = default;
Logger& Logger::operator=(Logger&&) = default;

void Logger::log(const std::string & log) {
  if(impl) impl->log(log);
  else throw std::runtime_error{"Cannot log!"}; 
}
