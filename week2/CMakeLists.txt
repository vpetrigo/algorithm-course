cmake_minimum_required(VERSION 3.3)

set(helper_header_dir ${PROJECT_SOURCE_DIR}/helper)
include_directories(${helper_header_dir})

set(helper_headers ${helper_header_dir}/Prints.hpp)

set(dot_section dot_section.cpp ${helper_headers})
set(knapsack knapsack.cpp ${helper_headers})

add_executable(w2_task1 ${dot_section})
add_executable(w2_task2 ${knapsack})