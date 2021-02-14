cmake_minimum_required(VERSION 3.15)
#include(ExternalProject)

ADD_COMPILE_OPTIONS(-O0)

project(silo-main CXX)

set(CMAKE_VERBOSE_MAKEFILE true)

set(CMAKE_CXX_STANDARD 17)

add_library(silo-main
        simulator.cpp simulator.h)