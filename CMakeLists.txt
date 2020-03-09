cmake_minimum_required(VERSION 3.15)
project(silo-gui)

set(CMAKE_CXX_STANDARD 17)

include_directories("include")

find_package(SFML 2.5.1 COMPONENTS graphics REQUIRED)
add_executable(silo-gui src/main.cpp include/gui/component.h src/gui/component.cpp)
target_link_libraries(silo-gui sfml-graphics)