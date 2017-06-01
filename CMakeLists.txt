cmake_minimum_required(VERSION 3.7)
project(Personal_Library)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES library.cpp library.h)
add_library(Personal_Library ${SOURCE_FILES})