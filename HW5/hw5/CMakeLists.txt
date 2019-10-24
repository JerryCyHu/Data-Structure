cmake_minimum_required(VERSION 3.15)
project(hw5)

set(CMAKE_CXX_STANDARD 14)

include_directories(hw5)

add_executable(hw5
        hw5/essay.cpp
        hw5/essay.h
        hw5/essay_iterator.h
        hw5/main.cpp
        hw5/node.cpp
        hw5/node.h)
