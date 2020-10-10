cmake_minimum_required(VERSION 3.15)
project(silo-gui CXX)

set(CMAKE_VERBOSE_MAKEFILE true)

set(CMAKE_CXX_STANDARD 17)

include_directories("include")
#include_directories("tinyxml2")

#find_package(SFML 2.5.1 COMPONENTS graphics network REQUIRED)
#target_link_libraries(silo-gui sfml-graphics sfml-network)
include_directories("silo-newc")
add_subdirectory(src)
target_link_libraries(silo-gui ${CMAKE_SOURCE_DIR}/libsilo-newc.a)

#if (WIN32)
#	target_link_libraries(silo-gui ws2_32)
#else (WIN32)
#
#endif (WIN32)