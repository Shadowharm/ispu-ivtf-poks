cmake_minimum_required(VERSION 3.29)
project(parallel_programming)

set(CMAKE_CXX_STANDARD 20)

# Add MPI Package to Project
find_package(MPI REQUIRED)

add_executable(parallel_programming main.cpp
        lab1/lab1.cpp
        lab1/lab1.h
        lab2/lab2.cpp
        lab2/lab2.h
        lab3/lab3.cpp
        lab3/lab3.h)

# Link MPI libraries
target_link_libraries(parallel_programming PRIVATE MPI::MPI_CXX)
