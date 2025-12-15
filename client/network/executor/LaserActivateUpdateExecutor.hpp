/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** LaserActiveUpdate executor
*/

#ifndef LASERACTIVEUPDATE_EXECUTOR_HPP
#define LASERACTIVEUPDATE_EXECUTOR_HPP

#include "client/states/game/logic.hpp"

#include <memory>
#include <network/packets/listener/PacketExecutor.hpp>
#include <network/packets/impl/LaserActiveUpdatePacket.hpp>

class LaserActiveUpdateExecutor : public PacketExecutorImplClient
<LaserActiveUpdatePacket, ClientPollable>
{
public:
    LaserActiveUpdateExecutor(InGameStateLogic &logic) : logic(logic) {}

    bool execute([[maybe_unused]]Client &cl,
                 [[maybe_unused]] std::shared_ptr<ClientPollable> &con,
                 [[maybe_unused]] std::shared_ptr<LaserActiveUpdatePacket> packet)
    {
        this->logic.updateLaser(packet->getEntityId(), packet->isActive()
                                , packet->getLength());
        return true;
    }

    int getPacketId() const {
        return PacketId::LASER_ACTIVE_UPDATE;
    }
private:
    [[maybe_unused]] InGameStateLogic &logic;
};

#endif /* LASERACTIVEUPDATE_EXECUTOR_HPP */
