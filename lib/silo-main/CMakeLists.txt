cmake_minimum_required(VERSION 3.15)
project(silo-main C)
set(CMAKE_C_STANDARD 11)

set(CMAKE_VERBOSE_MAKEFILE true)
set(PATH_LIB ${CMAKE_CURRENT_SOURCE_DIR}/src/lib)

add_subdirectory(src)

add_library(
    base
    STATIC
    ${PATH_LIB}/Gates.c
    ${PATH_LIB}/Memory.c
)

add_compile_options(-lpthread -g -O0)

target_link_libraries(
    silo-main
    base
    pthread
)
