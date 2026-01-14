/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** NewBullet executor
*/

#ifndef NEWBULLET_EXECUTOR_HPP
#define NEWBULLET_EXECUTOR_HPP

#include "client/state_machine/states/game/Game.hpp"

#include <iostream>
#include <memory>
#include <network/packets/listener/PacketExecutor.hpp>
#include <network/packets/impl/SpawnStraightMovingEntityPacket.hpp>

class NewBulletExecutor : public PacketExecutorImplClient
<SpawnStraightMovingEntityPacket, ClientPollable>
{
public:
    NewBulletExecutor(Game &state) : state(state) {}

    bool execute([[maybe_unused]] Client &cl,
                 [[maybe_unused]] std::shared_ptr<ClientPollable> con,
                 [[maybe_unused]] std::shared_ptr
        <SpawnStraightMovingEntityPacket> packet)
    {
        this->state.newBullet(packet->getMovingEntities());
        return true;
    }

    int getPacketId() const {
        return PacketId::SPAWN_STRAIGHT_MOVING_ENTITY_PACKET;
    }
private:
    [[maybe_unused]] Game &state;
};

#endif /* NEWBULLET_EXECUTOR_HPP */
