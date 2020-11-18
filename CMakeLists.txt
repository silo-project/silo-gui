cmake_minimum_required(VERSION 3.15)
include(cmake/ExternalProject.cmake)

project(silo-gui CXX)

set(CMAKE_VERBOSE_MAKEFILE true)

set(CMAKE_CXX_STANDARD 17)

# git clone https://libwebsockets.org/repo/libwebsockets -b v4.1-stable
#  in lib/
# configure to output to build/
# and make
# https://libwebsockets.org/lws-api-doc-master/html/md_README.build.html
# https://slproweb.com/products/Win32OpenSSL.html 1.1.1b

find_package(OpenSSL REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIR})
#link_directories(${OPENSSL_LIBRARY_DIR})
message(STATUS "Using OpenSSL ${OPENSSL_VERSION} ${OPENSSL_LIBRARIES}")

include_directories(${CMAKE_SOURCE_DIR}/lib/libwebsockets/build/include/)

add_subdirectory(src)

target_link_libraries(silo-gui ${CMAKE_SOURCE_DIR}/lib/libwebsockets/build/lib/libwebsockets_static.a)
target_link_libraries(silo-gui ${OPENSSL_LIBRARIES})

#add_dependencies(silo-gui uWebSockets)

if (WIN32)
	target_link_libraries(silo-gui ws2_32)
else (WIN32)

endif (WIN32)