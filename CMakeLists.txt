cmake_minimum_required(VERSION 3.15)
include(cmake/ExternalProject.cmake)

project(silo-gui CXX)

set(CMAKE_VERBOSE_MAKEFILE true)

set(CMAKE_CXX_STANDARD 17)

# https://github.com/etr/libhttpserver/blob/0.18.2/README.md
# 0.18.2 lib에 받아놓을 것

add_subdirectory(src)

#target_link_libraries(silo-gui ${CMAKE_SOURCE_DIR}/lib/libwebsockets/build/lib/libwebsockets_static.a)

if (WIN32)
	target_link_libraries(silo-gui ws2_32)
else (WIN32)

endif (WIN32)