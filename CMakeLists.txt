cmake_minimum_required(VERSION 3.8)
project(pageRank)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp matrix.cpp matrix.h)
add_executable(pageRank ${SOURCE_FILES})