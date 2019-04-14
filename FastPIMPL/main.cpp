#include <iostream>
#include "logger/Logger.hpp"

/*
 * Fast / static PIMPL
 * Used to address overhead of classic PIMPL related to 
 * using pointer and dynamic memory allocation.
 * It's relying on placement new operator to create object in 
 * pre-allocated memory.
 */

int main()
{
  Logger logger;
  logger.log("Some error!");
  return 0;
}