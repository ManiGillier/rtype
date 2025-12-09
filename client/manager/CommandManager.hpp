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
#include <mutex>
#include <queue>
#include <type_traits>


class CommandManager
{
public:
    template<class CommandType, class... Args>
    auto sendCommandToLogic(Args&&... args) -> void
    {
        this->logicMutex.lock();
        this->logicQueue.push(std::make_unique<CommandType>(args...));
        this->logicMutex.unlock();
    }
    template<class CommandType, class... Args>
    auto sendCommandToRender(Args&&... args) -> void
    {
        this->renderMutex.lock();
        this->renderQueue.push(std::make_unique<CommandType>(args...));
        this->renderMutex.unlock();
    }

    auto readLogicCommands() -> std::queue<std::unique_ptr<Command>>;
    auto readRenderCommands() -> std::queue<std::unique_ptr<Command>>;
private:
    std::queue<std::unique_ptr<Command>> logicQueue;
    std::queue<std::unique_ptr<Command>> renderQueue;
    std::mutex logicMutex;
    std::mutex renderMutex;
};

#endif /* CLIENT_COMMAND_MANAGER_HPP */
