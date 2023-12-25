cmake_minimum_required(VERSION 3.26)
project(matrix)

set(CMAKE_CXX_STANDARD 17)

add_executable(matrix matrix.cpp
        matrix.hpp)
