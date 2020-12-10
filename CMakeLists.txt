cmake_minimum_required(VERSION 3.15)
include(ExternalProject)

project(silo-gui CXX)

set(CMAKE_VERBOSE_MAKEFILE true)

set(CMAKE_CXX_STANDARD 17)

ExternalProject_Add(utility_silo-main
        BUILD_IN_SOURCE true
        GIT_REPOSITORY https://github.com/silo-project/silo-main.git
        GIT_TAG origin/lib
        SOURCE_DIR ${CMAKE_SOURCE_DIR}/lib/silo-main)

# https://github.com/yhirose/cpp-httplib 0.7.15
# https://github.com/leethomason/tinyxml2 8.0.0
# https://zlib.net 1.2.11
# ZLIB.dll 옮겨 놓을 것
# http://download.savannah.gnu.org/releases/tinycc/ 0.9.27
# Windows 라면 tcc win32 디렉터리에서 빌드 후 libtcc.dll 옮겨 놓을 것
# xNIX라면 알아서 하고 여기 추가할 것
# silo-main 레포 lib 브랜치 그대로 복사해 놓을 것

include_directories(${CMAKE_SOURCE_DIR}/lib/cpp-httplib-0.7.15)
include_directories(${CMAKE_SOURCE_DIR}/lib/tinyxml2-8.0.0)
include_directories(${CMAKE_BINARY_DIR}/lib/zlib-1.2.11)
include_directories(${CMAKE_SOURCE_DIR}/lib/zlib-1.2.11)
include_directories(${CMAKE_SOURCE_DIR}/lib/silo-main/src/include)

add_library(ntinyxml2 ${CMAKE_SOURCE_DIR}/lib/tinyxml2-8.0.0/tinyxml2.cpp ${CMAKE_SOURCE_DIR}/lib/tinyxml2-8.0.0/tinyxml2.h)

add_subdirectory(${CMAKE_SOURCE_DIR}/lib/zlib-1.2.11)
add_subdirectory(${CMAKE_SOURCE_DIR}/lib/cpp-httplib-0.7.15)
add_subdirectory(${CMAKE_SOURCE_DIR}/lib/silo-main)

if (WIN32)
    include_directories(${CMAKE_SOURCE_DIR}/lib/tcc-0.9.27/win32/libtcc)
else (WIN32)

endif (WIN32)

add_subdirectory(src)

target_link_libraries(silo-gui silo-main ntinyxml2 zlib httplib)

if (WIN32)
    target_link_libraries(silo-gui ws2_32 ${CMAKE_SOURCE_DIR}/lib/tcc-0.9.27/win32/lib/libtcc1-64.a)
else (WIN32)
    target_link_libraries(silo-gui ${CMAKE_SOURCE_DIR}/lib/tcc-0.9.27/lib/libtcc1-64.a)
endif (WIN32)