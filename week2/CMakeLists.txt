cmake_minimum_required(VERSION 3.3)

set(helper_header_dir ${PROJECT_SOURCE_DIR}/helper)
include_directories(${helper_header_dir})

set(helper_headers ${helper_header_dir}/Prints.hpp)

set(dot_section dot_section.cpp ${helper_headers})
set(knapsack knapsack.cpp ${helper_headers})
set(dif_components dif_components.cpp ${helper_headers})
set(huffman_enc huffman_enc.cpp ${helper_headers})
set(huffman_dec huffman_dec.cpp ${helper_headers})
set(priority_queue priority_queue.cpp ${helper_headers})

add_executable(w2_task1 ${dot_section})
add_executable(w2_task2 ${knapsack})
add_executable(w2_task3 ${dif_components})
add_executable(w2_task5 ${huffman_enc})
add_executable(w2_task6 ${huffman_dec})
add_executable(w2_task7 ${priority_queue})