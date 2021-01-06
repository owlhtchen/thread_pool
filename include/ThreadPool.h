#ifndef THREAD_POOL_H
#define THREAD_POOL_H
#include <thread>
#include <deque>
#include <functional>
#include <mutex>
#include <condition_variable>

class ThreadPool {
    public:
    unsigned int numThreads;
    std::vector<std::thread> threads;
    std::deque<std::function<void()>> tasks;
    std::mutex tasksMutex;
    std::condition_variable notEmpty;

    bool endPool;
    
    ThreadPool(): endPool(false), numThreads(std::thread::hardware_concurrency()) { 
        createWorkers(numThreads);
    };
    ThreadPool(unsigned int numThreads): endPool(false), numThreads(numThreads) { 
        createWorkers(numThreads);
    };

    void add(std::function<void()> task) {
        {
            std::lock_guard<std::mutex> lock(tasksMutex);
            tasks.push_back(task);
            notEmpty.notify_all();
        }
    }

    void createWorkers(unsigned int numWorkers) {
        numWorkers = numWorkers > 0 ? numWorkers : 1;
        for(int i = 0; i < numWorkers; i++) {
            threads.emplace_back([&](){worker();}); 
            // threads.emplace_back(worker); // worker is a method, cannot be called independent of object
        }
    }

    void worker() {
        while(endPool) {
            std::unique_lock<std::mutex> lk(tasksMutex);
            notEmpty.wait(lk, [&](){ return !tasks.empty() || endPool; });
            if(!endPool) {
                auto current = std::move(tasks.front());
                tasks.pop_front();
                lk.unlock();
                current();
            }
        }
    }

    void waitAll() {

    }
};

#endif