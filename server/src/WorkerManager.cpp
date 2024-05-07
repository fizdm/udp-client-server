#include "WorkerManager.hpp"

WorkerManager::WorkerManager(uint16_t nWorkers) {
    for (uint16_t i = 0; i < nWorkers; ++i) {
        workers_.emplace_back([&]() {
            while (isRunning_.load(std::memory_order_relaxed)) {
                run();
            }
        });
    }

    isRunning_.store(true, std::memory_order_relaxed);
}

WorkerManager::~WorkerManager() {
    isRunning_.store(false, std::memory_order_relaxed);

    for (auto& thread : workers_) {
        if (thread.joinable()) {
            thread.join();
        }
    }
}

void WorkerManager::run() {
    std::unique_lock lock(queueMutex_);
    queueCondVar_.wait(lock, [&]() {
        return !tasks_.empty();
    });

    auto task = tasks_.front();
    tasks_.pop();

    task();
}
