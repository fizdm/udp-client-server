#ifndef WORKERMANAGER_HPP
#define WORKERMANAGER_HPP

#include <cstdint>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <shared_mutex>
#include <queue>
#include <thread>
#include <atomic>

class WorkerManager {
public:
    explicit WorkerManager(uint16_t nWorkers = 4);
    ~WorkerManager();

    void Emplace(const std::function<void()> &func)
    {
        std::unique_lock lock(queueMutex_);
        tasks_.push(func);
        queueCondVar_.notify_one();
    }


private:
    std::mutex queueMutex_;
    std::condition_variable queueCondVar_;

    std::queue<std::function<void()>> tasks_;
    std::vector<std::thread> workers_;

    std::atomic<bool> isRunning_{false};

    void run();
};


#endif //WORKERMANAGER_HPP
