cmake_minimum_required(VERSION 3.3)
project(algorithm_course)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(helper)

add_subdirectory(week1)
add_subdirectory(week2)
add_subdirectory(week3)