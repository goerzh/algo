cmake_minimum_required(VERSION 2.6)
project(algo C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(src)

add_executable(vec_test tests/vec_test.cpp)
add_executable(list_test tests/list_test.cpp)