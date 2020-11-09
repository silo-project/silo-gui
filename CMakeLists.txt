cmake_minimum_required(VERSION 3.15)
include(cmake/ExternalProject.cmake)

project(silo-gui CXX)

set(CMAKE_VERBOSE_MAKEFILE true)

set(CMAKE_CXX_STANDARD 17)

ExternalProject_Add(uWebSockets
        GIT_REPOSITORY https://github.com/uNetworking/uWebSockets.git
        GIT_TAG v18.15.0
        PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/uWebSockets
        SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/uWebSockets
        CONFIGURE_COMMAND ""
        BUILD_COMMAND "${MAKE}"
        INSTALL_COMMAND ""
)

add_subdirectory(src)

add_dependencies(silo-gui uWebSockets)

#if (WIN32)
#	target_link_libraries(silo-gui ws2_32)
#else (WIN32)
#
#endif (WIN32)