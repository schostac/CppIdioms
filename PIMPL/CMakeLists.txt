cmake_minimum_required(VERSION 3.5)

project(PimplExample)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(logger)

include_directories(${PROJECT_SOURCE_DIR}/logger/include)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} logger)