cmake_minimum_required(VERSION 3.29)
project(parallel_programming)

set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_CXX_COMPILER /opt/homebrew/bin/g++-14)

# Add MPI Package to Project
find_package(MPI REQUIRED)
find_package(OpenMP REQUIRED)
#set_target_properties(main PROPERTIES LINKER_LANGUAGE CXX)


add_executable(parallel_programming main.cpp
        lab1/lab1.cpp
        lab1/lab1.h
        lab2/lab2.cpp
        lab2/lab2.h
        lab3/lab3.cpp
        lab3/lab3.h
        lab4/lab4.cpp
        lab4/lab4.h
        lab5/lab5.cpp
        lab5/lab5.h
        task1/task1.cpp
        task1/task1.h
        lab7/lab7.cpp
        lab7/lab7.h
        lab8/lab8.cpp
        lab8/lab8.h
        lab9/lab9.cpp
        lab9/lab9.h
        task2/task2.cpp
        task2/task2.h
        lab10/lab10.cpp
        lab10/lab10.h)

# Link MPI libraries
target_link_libraries(parallel_programming PRIVATE MPI::MPI_CXX)

#TJR find_package(OpenMP)
#set(OPENMP_FOUND TRUE)
#set(OpenMP_CXX_FLAGS “-fopenmp”)
#TJR end edits

if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()
# Enable OpenMP support
#if (OpenMP_C_FOUND)
#    set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
#    target_link_libraries(Project1 PRIVATE ${OpenMP_CXX_LIBRARIES})
#endif ()