cmake_minimum_required(VERSION 3.2)

project(threadpool)
project(test_iife)

add_executable(main src/main.cpp)
add_executable(test_iife src/iife.cpp)

target_include_directories(main PUBLIC include)
target_include_directories(test_iife PUBLIC include)

