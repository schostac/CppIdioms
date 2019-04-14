#include <iostream>
#include "logger/Logger.hpp"

/*
 * PIMPL (pointer to implementation) idiom
 * - Breaks compile-time dependency between the implementation 
 * and the user of the class interface. Thus changes to 
 * the implemnetation do not require recompilation of all users.
 * - Hides private data members and member functions in 
 * the implementation class. 
 */

int main()
{
  Logger logger;
  logger.log("Some error!");
  return 0;
}