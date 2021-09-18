cmake_minimum_required(VERSION 3.17)
project(test_problem)

set(CMAKE_CXX_STANDARD 17)

add_executable(test_problem main.cpp Dot.cpp Dot.h Segment.cpp Segment.h initial_shell.cpp initial_shell.h)