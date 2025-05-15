cmake_minimum_required(VERSION 3.10)
project(P02)

set(CMAKE_CXX_STANDARD 20)

# Add all source files
add_executable(P02
        main.cpp
        polynomial.cpp
        polynomial_operations.cpp
        polynomial_io.cpp
)