#include <iostream>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include <ThreadPool.h>
#include <string>

int main() {
    ThreadPool pool;
    for(int i = 0; i < 10; i++) {
        [&](int num) {
            // std::cerr << "call add: " << num << std::endl;
            // std::this_thread::sleep_for(std::chrono::seconds(1));
            // threads.emplace_back([&]() { // capture by reference doesn't work since num is local and is deallocated onces lambda ends, so captured value is nonsense
            pool.add([=]() {
                if(num == 2) {
                    std::this_thread::sleep_for (std::chrono::seconds(10));
                }
                std::cerr << "from thread "<< std::this_thread::get_id() 
                        << " :" << (10000 + num) << std::endl;
                // num = 10; // a by copy capture cannot be modified in a non-mutable lambda 
            });
        }(i);
    } 
}