cmake_minimum_required(VERSION 3.15)
#include(cmake/ExternalProject.cmake)

project(silo-gui CXX)

set(CMAKE_VERBOSE_MAKEFILE true)

set(CMAKE_CXX_STANDARD 17)

# https://github.com/yhirose/cpp-httplib

include_directories(${CMAKE_SOURCE_DIR}/lib/cpp-httplib-0.7.15)

add_subdirectory(src)

if (WIN32)
	target_link_libraries(silo-gui ws2_32)
else (WIN32)

endif (WIN32)