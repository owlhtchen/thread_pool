#include <iostream>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include <ThreadPool.h>
#include <string>

void test(void) {
    std::cout << "test\n";
}

int main() {
    ThreadPool pool;
    std::cerr << "main thread is "<< std::this_thread::get_id() << std::endl;
    for(int i = 0; i < 4; i++) {
        pool.add([=]() {
            if(i == 2) {
                std::this_thread::sleep_for (std::chrono::seconds(10));
            }
            auto thread_id = std::this_thread::get_id();
            std::cerr << "from thread "<< thread_id
                    << " :" << (10000 + i) << std::endl;
        });
    }
    
    pool.waitAll();
    std::cout << "after waiting 1...\n";

    for(int i = 0; i < 10; i++) {
        pool.add([=]() {
            if(i == 2) {
                std::this_thread::sleep_for (std::chrono::seconds(10));
            }
            auto thread_id = std::this_thread::get_id();
            std::cerr << "from thread "<< thread_id
                    << " :" << (10000 + i) << std::endl;
        });
    }    
}