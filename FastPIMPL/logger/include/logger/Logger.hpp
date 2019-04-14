#pragma once

#include <string>
#include <cstddef>
#include <type_traits>

class Logger {
public:
  Logger();
  ~Logger();
  void log(const std::string&);
private:
  static constexpr std::size_t size = 1024;
  std::aligned_storage<size, std::alignment_of<std::max_align_t>::value>::type impl;
};