cmake_minimum_required(VERSION 3.14)
project(allocatorLK)

set(CMAKE_CXX_STANDARD 14)

add_executable(allocatorLK main.cpp list.cpp list.h allocator.cpp allocator.h test.cpp test.h)