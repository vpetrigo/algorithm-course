cmake_minimum_required(VERSION 3.3)

set(small_fib small_fib.cpp)
set(fib_num fib_num.cpp)

add_executable(task1 ${small_fib})
add_executable(task2 ${fib_num})
set_property(TARGET task1 PROPERTY CXX_STANDARD 14)
set_property(TARGET task2 PROPERTY CXX_STANDARD 14)