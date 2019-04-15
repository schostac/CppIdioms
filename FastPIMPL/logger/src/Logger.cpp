#include "logger/Logger.hpp"

#include <fstream>
#include <iostream>
#include <stdexcept>

namespace constants {
  static constexpr char fileName[] = "MyLogs.txt";
}

class LoggerImpl {
public:
  LoggerImpl(): file(constants::fileName) {
    if(not file.is_open()) 
      throw std::runtime_error{"Cannot open file!"};
  }

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