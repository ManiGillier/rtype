#include "ThreadPool.hpp"
#include <chrono>
#include <future>

ThreadPool::~ThreadPool()
{
    waitAll();
}

void ThreadPool::waitAll()
{
    std::unique_lock<std::mutex> lock(_mutex);
    std::vector<std::future<void>> localFutures = std::move(_futures);
    lock.unlock();

    for (auto &future : localFutures) {
        if (future.valid()) {
            future.wait();
        }
    }
}

std::size_t ThreadPool::activeTaskCount()
{
    std::lock_guard<std::mutex> lock(_mutex);
    cleanup();
    return _futures.size();
}

// remove finished thread
void ThreadPool::cleanup()
{
    for (auto it = _futures.begin(); it != _futures.end();) {
        if (it->wait_for(std::chrono::seconds(0)) ==
            std::future_status::ready) {
            it = _futures.erase(it);
        } else
            it++;
    }
}
