cmake_minimum_required(VERSION 3.14)
project(STL)

set(CMAKE_CXX_STANDARD 17)

add_executable(STL main.cpp alloc.h allocator.h construct.h)