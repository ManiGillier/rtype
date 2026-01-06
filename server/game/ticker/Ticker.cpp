#include "Ticker.hpp"
#include <thread>

Ticker::Ticker(int ticks)
{
    _ticks = std::chrono::milliseconds(1000 / ticks);
}

void Ticker::now()
{
    _start = std::chrono::steady_clock::now();
}

void Ticker::wait()
{
    auto endTime = std::chrono::steady_clock::now();
    auto elapsed =
        std::chrono::duration_cast<std::chrono::milliseconds>(endTime - _start);
    auto sleepTime = _ticks - elapsed;
    if (sleepTime.count() > 0) {
        std::this_thread::sleep_for(sleepTime);
    }
}
