cmake_minimum_required(VERSION 3.14)
project(STL)

set(CMAKE_CXX_STANDARD 17)

add_executable(STL alloc.h allocator.h construct.h iterator.h typetratis.h utility.h algorithm.h functional.h main.cpp reverseiterator.h uninitializedfunctions.h)