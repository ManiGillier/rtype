/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** TimeNow executor
*/

#ifndef TIMENOW_EXECUTOR_HPP
#define TIMENOW_EXECUTOR_HPP

#include "client/state_machine/states/game/Game.hpp"

#include <memory>
#include <network/packets/listener/PacketExecutor.hpp>
#include <network/packets/impl/TimeNowPacket.hpp>

class TimeNowExecutor : public PacketExecutorImplClient
<TimeNowPacket, ClientPollable>
{
public:
    TimeNowExecutor(Game &state) : state(state) {}

    bool execute([[maybe_unused]] Client &cl,
                 [[maybe_unused]] std::shared_ptr<ClientPollable> con,
                 [[maybe_unused]] std::shared_ptr<TimeNowPacket> packet)
    {
        this->state.setTime(packet->getTime());
        return true;
    }

    int getPacketId() const {
        return PacketId::TIME_NOW_PACKET;
    }
private:
    [[maybe_unused]] Game &state;
};

#endif /* TIMENOW_EXECUTOR_HPP */
