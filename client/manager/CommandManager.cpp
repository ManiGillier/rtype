/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** command manager
*/

#include "CommandManager.hpp"
#include <memory>

auto CommandManager::readLogicCommands()
    -> std::queue<std::unique_ptr<Command>>
{
    this->logicMutex.lock();
    std::queue<std::unique_ptr<Command>> queue = std::move(this->logicQueue);
    this->logicMutex.unlock();
    return queue;
}

auto CommandManager::readRenderCommands()
    -> std::queue<std::unique_ptr<Command>>
{
    this->renderMutex.lock();
    std::queue<std::unique_ptr<Command>> queue = std::move(this->renderQueue);
    this->renderMutex.unlock();
    return queue;
}
