/*
** EPITECH PROJECT, 2025
** arcade [WSL: Ubuntu-24.04]
** File description:
** Logger
*/

#ifndef LOGGER_HPP_
#define LOGGER_HPP_

#include <chrono>
#include <iostream>
#include <ostream>
#include <format>

class Logger {
    public:
        inline static bool shouldLog = false;
};

#define LOG(message) if (Logger::shouldLog) { std::cout << "[R-Type Network] [" << std::format("{:%d/%m/%Y %H:%M:%S}", floor<std::chrono::milliseconds>(std::chrono::system_clock::now())) << "] [*] " << message << std::endl; }

#define LOG_ERR(message) if (Logger::shouldLog) { std::cout << "[R-Type Network] [" << std::format("{:%d/%m/%Y %H:%M:%S}", floor<std::chrono::milliseconds>(std::chrono::system_clock::now())) << "] [*] " << message << std::endl; }

#define DEBUG LOG_ERR << __func__ << " - " << __FILE__        \
    << ":" << __LINE__ << std::endl;

#endif /* !LOGGER_HPP_ */
