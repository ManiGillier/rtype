/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** placeholder executor
*/

#ifndef PLACEHOLDER_EXECUTOR_HPP
#define PLACEHOLDER_EXECUTOR_HPP

#include "client/state_machine/states/game/Game.hpp"

#include <memory>
#include <network/packets/listener/PacketExecutor.hpp>
#include <network/packets/impl/PlaceholderPacket.hpp>

class PlaceholderExecutor : public PacketExecutorImplClient
<PlaceholderPacket, ClientPollable>
{
public:
    PlaceholderExecutor(Game &state) : state(state) {}

    bool execute([[maybe_unused]]Client &cl,
                 [[maybe_unused]] std::shared_ptr<ClientPollable> con,
                 [[maybe_unused]] std::shared_ptr<PlaceholderPacket> packet)
    {
        this->state.(packet->getEntityId());
        return true;
    }

    int getPacketId() const {
        return PacketId::PLACEHOLDER;
    }
private:
    [[maybe_unused]] Game &state;
};

#endif /* PLACEHOLDER_EXECUTOR_HPP */
