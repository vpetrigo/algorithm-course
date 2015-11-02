cmake_minimum_required(VERSION 3.3)

set(helper_header_dir ${PROJECT_SOURCE_DIR}/helper)
include_directories(${helper_header_dir})

set(helper_headers ${helper_header_dir}/Prints.hpp)

set(small_fib small_fib.cpp)
set(fib_num fib_num.cpp)
set(large_fib large_fib.cpp)

add_executable(w1_task1 ${small_fib})
add_executable(w1_task2 ${fib_num})
add_executable(w1_task3 ${large_fib})
set_property(TARGET w1_task1 PROPERTY CXX_STANDARD 14)
set_property(TARGET w1_task2 PROPERTY CXX_STANDARD 14)
set_property(TARGET w1_task3 PROPERTY CXX_STANDARD 14)