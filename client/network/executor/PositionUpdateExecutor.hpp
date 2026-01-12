/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** PositionUpdate executor
*/

#ifndef POSITIONUPDATE_EXECUTOR_HPP
#define POSITIONUPDATE_EXECUTOR_HPP

#include "client/state_machine/states/game/Game.hpp"

#include <memory>
#include <network/packets/listener/PacketExecutor.hpp>
#include <network/packets/impl/PositionUpdatePacket.hpp>

class PositionUpdateExecutor : public PacketExecutorImplClient
<PositionUpdatePacket, ClientPollable>
{
public:
    PositionUpdateExecutor(Game &state) : state(state) {}

    bool execute([[maybe_unused]]Client &cl,
                 [[maybe_unused]] std::shared_ptr<ClientPollable> con,
                 [[maybe_unused]] std::shared_ptr<PositionUpdatePacket> packet)
    {
        this->state.updatePosition(packet->getEntityId(), packet->getXPos(),
                                   packet->getYPos());
        return true;
    }

    int getPacketId() const {
        return PacketId::POSITION_UPDATE;
    }
private:
    [[maybe_unused]] Game &state;
};

#endif /* POSITIONUPDATE_EXECUTOR_HPP */
