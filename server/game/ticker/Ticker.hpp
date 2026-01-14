/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** ticker
*/

#ifndef TICKER_HPP
#define TICKER_HPP

#include <chrono>

class Ticker
{
  public:
    Ticker(int ticks_by_sec);
    ~Ticker() = default;
    std::chrono::steady_clock::time_point now();
    void wait();

  private:
    std::chrono::milliseconds _ticks;
    std::chrono::time_point<std::chrono::steady_clock> _start;
};

#endif
