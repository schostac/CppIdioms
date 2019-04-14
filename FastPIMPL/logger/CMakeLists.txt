cmake_minimum_required(VERSION 3.5)

project(logger)

include_directories(${PROJECT_SOURCE_DIR}/include)

set(SOURCE ${PROJECT_SOURCE_DIR}/src/Logger.cpp)

add_library(${PROJECT_NAME} STATIC ${SOURCE})