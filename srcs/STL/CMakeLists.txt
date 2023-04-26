cmake_minimum_required(VERSION 3.22)
project(STL)

set(CMAKE_CXX_STANDARD 14)

add_executable(STL main.cpp stl_vector.h stl_pair.h stl_list.h)
