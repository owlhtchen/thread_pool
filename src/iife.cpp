#include <iostream>
#include <thread>
#include <vector>

int main() {
    std::vector<std::thread> threads;
    for(int i = 0; i < 4; i++) {
        [&](int num) {
            // std::cerr << "call add: " << num << std::endl;
            // std::this_thread::sleep_for(std::chrono::seconds(1));
            // threads.emplace_back([&]() { // capture by reference doesn't work since num is local and is deallocated onces lambda ends, so captured value is nonsense
            threads.emplace_back([=]() {
                if(num == 2) {
                    std::this_thread::sleep_for (std::chrono::seconds(10));
                }
                std::cerr << "from thread "<< std::this_thread::get_id() 
                        << " :" << (10000 + num) << std::endl;
                // num = 10; // a by copy capture cannot be modified in a non-mutable lambda 
            });
        }(i);
    } 
    for(auto& t: threads) {
        t.join();
    }
}