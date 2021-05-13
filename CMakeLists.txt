cmake_minimum_required(VERSION 3.2)

project(threadpool)
project(test_iife)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(main src/main.cpp)
add_executable(test_iife src/iife.cpp)
add_executable(pooliife src/pooliife.cpp)

target_include_directories(main PUBLIC include)
target_include_directories(test_iife PUBLIC include)
target_include_directories(pooliife PUBLIC include)

target_link_libraries(main PRIVATE Threads::Threads)
target_link_libraries(test_iife PRIVATE Threads::Threads)
target_link_libraries(pooliife PRIVATE Threads::Threads)
