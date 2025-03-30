cmake_minimum_required(VERSION 3.29)
project(asd)

set(CMAKE_CXX_STANDARD 20)

add_executable(asd main.cpp
        lab1/lab1.cpp
        lab1/lab1.h
        lab2/lab2.cpp
        lab2/lab2.h
        pk1/ostov/BFS.cpp
        pk1/ostov/BFS.h
        pk1/ostov/DFS.cpp
        pk1/ostov/DFS.h
        pk1/findCyclesUtil/findCyclesUtil.cpp
        pk1/findCyclesUtil/findCyclesUtil.h
        lab3/lab3.cpp
        lab3/lab3.h
        lab4/lab4.cpp
        lab4/lab4.h
        walk_down/walk_down.cpp
        walk_down/walk_down.h
        rle/rle_proto.cpp
        rle/rle_proto.h)
