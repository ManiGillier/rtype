/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** NewEnemy executor
*/

#ifndef NEWENEMY_EXECUTOR_HPP
#define NEWENEMY_EXECUTOR_HPP

#include "client/states/game/logic.hpp"

#include <iostream>
#include <memory>
#include <network/packets/listener/PacketExecutor.hpp>
#include <network/packets/impl/NewEnemyPacket.hpp>

class NewEnemyExecutor : public PacketExecutorImplClient
<NewEnemyPacket, ClientPollable>
{
public:
    NewEnemyExecutor(InGameStateLogic &logic) : logic(logic) {}

    bool execute([[maybe_unused]] Client &cl,
                 [[maybe_unused]] std::shared_ptr<ClientPollable> con,
                 [[maybe_unused]] std::shared_ptr<NewEnemyPacket> packet)
    {
        this->logic.newEnemy(packet->getEntityId());
        return true;
    }

    int getPacketId() const {
        return PacketId::NEW_ENEMY;
    }
private:
    [[maybe_unused]] InGameStateLogic &logic;
};

#endif /* NEWENEMY_EXECUTOR_HPP */
