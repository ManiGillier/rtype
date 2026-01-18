/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** NewEnemy executor
*/

#ifndef NEWENEMY_EXECUTOR_HPP
#define NEWENEMY_EXECUTOR_HPP

#include "client/state_machine/states/game/Game.hpp"

#include <iostream>
#include <memory>
#include <network/packets/listener/PacketExecutor.hpp>
#include <network/packets/impl/NewEnemyPacket.hpp>

class NewEnemyExecutor : public PacketExecutorImplClient
<NewEnemyPacket, ClientPollable>
{
public:
    NewEnemyExecutor(Game &state) : state(state) {}

    bool execute([[maybe_unused]] Client &cl,
                 [[maybe_unused]] std::shared_ptr<ClientPollable> con,
                 [[maybe_unused]] std::shared_ptr<NewEnemyPacket> packet)
    {
        this->state.newEnemy(packet->getEntityId(), packet->getType());
        return true;
    }

    int getPacketId() const {
        return PacketId::NEW_ENEMY;
    }
private:
    [[maybe_unused]] Game &state;
};

#endif /* NEWENEMY_EXECUTOR_HPP */
