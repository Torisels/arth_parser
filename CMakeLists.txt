# cmake_minimum_required(VERSION <specify CMake version here>)
project(parser C)

set(CMAKE_C_STANDARD 99)

add_executable(parser main.c stack.c stack.h)