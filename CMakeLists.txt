cmake_minimum_required(VERSION 3.15)
project(silo-gui)

set(CMAKE_CXX_STANDARD 17)

include_directories("include")

find_package(SFML 2.5.1 COMPONENTS graphics network REQUIRED)
add_executable(silo-gui src/main.cpp src/comm/corecomm.cpp src/tinyxml2/tinyxml2.cpp src/file/circreader.cpp src/file/circuit.cpp src/file/part.cpp src/file/partmanager.cpp)
target_link_libraries(silo-gui sfml-graphics sfml-network)

#if (WIN32)
#	target_link_libraries(silo-gui ws2_32)
#else (WIN32)
#
#endif (WIN32)