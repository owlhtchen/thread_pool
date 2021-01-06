cmake_minimum_required(VERSION 3.2)

project(threadpool)

add_executable(main src/main.cpp)

target_include_directories(main PUBLIC include)

