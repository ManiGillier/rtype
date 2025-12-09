/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** command manager
*/

#include "CommandManager.hpp"
#include <memory>

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
