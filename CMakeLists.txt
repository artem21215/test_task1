cmake_minimum_required(VERSION 3.17)
project(test_problem)

set(CMAKE_CXX_STANDARD 17)

add_executable(test_problem main.cpp Dot.cpp Dot.h Segment.cpp Segment.h initial_shell.cpp initial_shell.h point_location.cpp point_location.h segment_location.cpp segment_location.h build_scanline.cpp build_scanline.h intersection_dot_with_segment.cpp intersection_dot_with_segment.h)