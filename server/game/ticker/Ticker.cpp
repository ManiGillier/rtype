#include "Ticker.hpp"
#include <thread>

Ticker::Ticker(int ticks)
{
    _ticks = std::chrono::milliseconds(1000 / ticks);
}

 std::chrono::steady_clock::time_point Ticker::now()
{
    auto now = std::chrono::steady_clock::now();
    _start = now;
    return now;
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
