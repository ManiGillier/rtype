/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** command manager
*/

#include "CommandManager.hpp"
#include <memory>

template<class CommandType, std::is_base_of<CommandType, Command>>
auto CommandManager::sendCommandToLogic(CommandType const &c)
    -> void
{
    this->logicQueue.push(std::make_unique<CommandType>(c));
}

template<class CommandType, std::is_base_of<CommandType, Command>>
auto CommandManager::sendCommandToRender(CommandType const &c)
    -> void
{
    this->renderQueue.push(std::make_unique<CommandType>(c));
}


auto CommandManager::readLogicCommands()
    -> std::queue<std::unique_ptr<Command>>&
{
    return this->logicQueue;
}

auto CommandManager::readRenderCommands()
    -> std::queue<std::unique_ptr<Command>>&
{
    return this->renderQueue;
}
