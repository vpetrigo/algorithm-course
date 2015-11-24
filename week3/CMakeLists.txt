cmake_minimum_required(VERSION 3.3)

set(helper_header_dir ${PROJECT_SOURCE_DIR}/helper)
include_directories(${helper_header_dir})

set(helper_headers ${helper_header_dir}/Prints.hpp)

set(binary_search binary_search.cpp ${helper_headers})
set(merge_sort merge_sort.cpp ${helper_headers})
set(quick_sort quick_sort.cpp ${helper_headers})
set(count_sort count_sort.cpp ${helper_headers})

add_executable(w3_task1 ${binary_search})
add_executable(w3_task3 ${merge_sort})
add_executable(w3_task4 ${quick_sort})
add_executable(w3_task8 ${count_sort})