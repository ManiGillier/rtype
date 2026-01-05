/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** threadPool
*/

#ifndef THREAD_POOL_HPP
#define THREAD_POOL_HPP

#include <future>
#include <mutex>
#include <vector>

class ThreadPool
{
  public:
    ThreadPool() = default;
    ~ThreadPool();

    template <typename F, typename... Args>
    void push_task(F &&f, Args &&...args)
    {
        std::lock_guard<std::mutex> lock(_mutex);
        this->cleanup();
        _futures.push_back(std::async(std::launch::async, 
            std::forward<F>(f),
            std::forward<Args>(args)...));
    }
    std::size_t activeTaskCount();
    void cleanup();
    void waitAll();

  private:
    std::vector<std::future<void>> _futures;
    std::mutex _mutex;
};

#endif
