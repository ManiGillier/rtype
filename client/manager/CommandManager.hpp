/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** command manager
*/

#ifndef CLIENT_COMMAND_MANAGER_HPP
#define CLIENT_COMMAND_MANAGER_HPP

#include "client/commands/Command.hpp"

#include <memory>
#include <queue>
#include <type_traits>


class CommandManager
{
public:
    template<class CommandType, std::is_base_of<CommandType, Command>>
    auto sendCommandToLogic(CommandType const &) -> void;
    template<class CommandType, std::is_base_of<CommandType, Command>>
    auto sendCommandToRender(CommandType const &) -> void;

    auto readLogicCommands() -> std::queue<std::unique_ptr<Command>>&;
    auto readRenderCommands() -> std::queue<std::unique_ptr<Command>>&; 
private:
    std::queue<std::unique_ptr<Command>> logicQueue;
    std::queue<std::unique_ptr<Command>> renderQueue;
};

#endif /* CLIENT_COMMAND_MANAGER_HPP */
