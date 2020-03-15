cmake_minimum_required(VERSION 2.6)
project(algo C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(src)
add_subdirectory(src)

add_executable(vec_test tests/vec_test.cpp)
add_executable(list_test tests/list_test.cpp)
add_executable(test_skiplist tests/test_skiplist.cpp)
add_executable(test_hashmap tests/test_hashmap.cpp)
add_executable(test_binary_search_tree tests/test_binary_search_tree.cpp)
add_executable(test_red_black_tree tests/test_red_black_tree.cpp)
add_executable(test_btree tests/test_btree.cpp)
