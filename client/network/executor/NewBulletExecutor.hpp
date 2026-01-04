/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** NewBullet executor
*/

#ifndef NEWBULLET_EXECUTOR_HPP
#define NEWBULLET_EXECUTOR_HPP

#include "client/states/game/logic.hpp"

#include <iostream>
#include <memory>
#include <network/packets/listener/PacketExecutor.hpp>
#include <network/packets/impl/NewBulletPacket.hpp>

class NewBulletExecutor : public PacketExecutorImplClient
<NewBulletPacket, ClientPollable>
{
public:
    NewBulletExecutor(InGameStateLogic &logic) : logic(logic) {}

    bool execute([[maybe_unused]] Client &cl,
                 [[maybe_unused]] std::shared_ptr<ClientPollable> con,
                 [[maybe_unused]] std::shared_ptr<NewBulletPacket> packet)
    {
        this->logic.newBullet(packet->getEntityId());
        return true;
    }

    int getPacketId() const {
        return PacketId::NEW_BULLET;
    }
private:
    [[maybe_unused]] InGameStateLogic &logic;
};

#endif /* NEWBULLET_EXECUTOR_HPP */
