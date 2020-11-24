cmake_minimum_required(VERSION 3.15)
#include(cmake/ExternalProject.cmake)

project(silo-gui CXX)

set(CMAKE_VERBOSE_MAKEFILE true)

set(CMAKE_CXX_STANDARD 17)

# https://github.com/yhirose/cpp-httplib 0.7.15
# https://github.com/leethomason/tinyxml2 8.0.0
# https://zlib.net 1.2.11
# ZLIB.dll 옮겨 놓을 것

add_subdirectory(${CMAKE_SOURCE_DIR}/lib/zlib-1.2.11)

include_directories(${CMAKE_SOURCE_DIR}/lib/cpp-httplib-0.7.15)
include_directories(${CMAKE_SOURCE_DIR}/lib/tinyxml2-8.0.0)
include_directories(${CMAKE_SOURCE_DIR}/lib/zlib-1.2.11)
include_directories(${CMAKE_SOURCE_DIR}/lib/hash-library)

add_subdirectory(src)

add_library(tinyxml2 ${CMAKE_SOURCE_DIR}/lib/tinyxml2-8.0.0/tinyxml2.cpp)
add_dependencies(silo-gui tinyxml2 zlib)

if (WIN32)
    target_link_libraries(silo-gui ws2_32)
endif (WIN32)