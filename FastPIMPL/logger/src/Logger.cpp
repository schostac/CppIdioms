#include "logger/Logger.hpp"

#include <fstream>
#include <iostream>

namespace constants {
  static constexpr char fileName[] = "MyLogs.txt";
}

class LoggerImpl {
public:
  LoggerImpl(): file(constants::fileName) {}
  void log(const std::string & info) { 
    std::cout << "Logging: " << info << std::endl;
    file << info << '\n'; 
  }
private:
  std::ofstream file;
};

Logger::Logger() {
  static_assert(sizeof(impl) >= sizeof(LoggerImpl));
  new(&impl) LoggerImpl;
}

Logger::~Logger() {
  reinterpret_cast<LoggerImpl*>(&impl)->~LoggerImpl();
}

void Logger::log(const std::string & info) {
  reinterpret_cast<LoggerImpl*>(&impl)->log(info); 
}