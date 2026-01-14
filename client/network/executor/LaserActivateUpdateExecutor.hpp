/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** LaserActiveUpdate executor
*/

#ifndef LASERACTIVEUPDATE_EXECUTOR_HPP
#define LASERACTIVEUPDATE_EXECUTOR_HPP

#include "client/state_machine/states/game/Game.hpp"

#include <memory>
#include <network/packets/listener/PacketExecutor.hpp>
#include <network/packets/impl/LaserActiveUpdatePacket.hpp>

class LaserActiveUpdateExecutor : public PacketExecutorImplClient
<LaserActiveUpdatePacket, ClientPollable>
{
public:
    LaserActiveUpdateExecutor(Game &state) : state(state) {}

    bool execute([[maybe_unused]] Client &cl,
                 [[maybe_unused]] std::shared_ptr<ClientPollable> con,
                 [[maybe_unused]] std::shared_ptr<LaserActiveUpdatePacket> packet)
    {
        this->state.updateLasers(packet->getLaserData());
        return true;
    }

    int getPacketId() const {
        return PacketId::LASER_ACTIVE_UPDATE;
    }
private:
    [[maybe_unused]] Game &state;
};

#endif /* LASERACTIVEUPDATE_EXECUTOR_HPP */
