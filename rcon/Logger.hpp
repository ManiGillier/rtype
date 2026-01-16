/*
** EPITECH PROJECT, 2026
** rtype [WSL: Ubuntu-24.04]
** File description:
** Logger
*/

#ifndef RCON_LOGGER_HPP_
    #define RCON_LOGGER_HPP_

    #define RCON_LOG(message) std::cout << "[R-Type RCON] [" << std::format("{:%d/%m/%Y %H:%M:%S}", floor<std::chrono::milliseconds>(std::chrono::system_clock::now())) << "] [*] " << message << std::endl

#endif /* !RCON_LOGGER_HPP_ */
