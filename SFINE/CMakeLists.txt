cmake_minimum_required(VERSION 3.5)

project(SFINE)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE ${PROJECT_SOURCE_DIR}/SFINE.cpp)

add_executable(${PROJECT_NAME} ${SOURCE})
