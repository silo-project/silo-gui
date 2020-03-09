cmake_minimum_required(VERSION 3.15)
project(silo-gui)

set(CMAKE_CXX_STANDARD 17)

include_directories("include")

find_package(SFML 2.5.1 COMPONENTS graphics network REQUIRED)
add_executable(silo-gui src/main.cpp src/comm/corecomm.cpp src/tinyxml/tinyxml.cpp src/tinyxml/tinyxmlerror.cpp src/tinyxml/tinyxmlparser.cpp src/tinyxml/tinystr.cpp)
target_link_libraries(silo-gui sfml-graphics sfml-network)

#if (WIN32)
#	target_link_libraries(silo-gui ws2_32)
#else (WIN32)
#
#endif (WIN32)