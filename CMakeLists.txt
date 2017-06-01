cmake_minimum_required(VERSION 3.7)
project(Personal_Library)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES cmake-build-debug/list.cpp cmake-build-debug/list.h cmake-build-debug/list_node.cpp cmake-build-debug/list_node.h cmake-build-debug/deque.cpp cmake-build-debug/deque.h)
add_library(Personal_Library ${SOURCE_FILES} cmake-build-debug/list.cpp cmake-build-debug/list.h)