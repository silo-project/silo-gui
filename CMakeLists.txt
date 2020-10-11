cmake_minimum_required(VERSION 3.15)
project(silo-gui CXX)

set(CMAKE_VERBOSE_MAKEFILE true)

set(CMAKE_CXX_STANDARD 17)

set(LIB_SILO-NEWC_DIR ${CMAKE_SOURCE_DIR}/lib/silo-newc)

include_directories("include")
#include_directories("tinyxml2")

#find_package(SFML 2.5.1 COMPONENTS graphics network REQUIRED)
#target_link_libraries(silo-gui sfml-graphics sfml-network)
include_directories(${LIB_SILO-NEWC_DIR})
add_subdirectory(src)
target_link_libraries(silo-gui ${LIB_SILO-NEWC_DIR}/libsilo-newc.a)

#if (WIN32)
#	target_link_libraries(silo-gui ws2_32)
#else (WIN32)
#
#endif (WIN32)