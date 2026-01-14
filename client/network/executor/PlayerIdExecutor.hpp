/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** PlayerId executor
*/

#ifndef PLAYERID_EXECUTOR_HPP
#define PLAYERID_EXECUTOR_HPP

#include "client/state_machine/states/game/Game.hpp"

#include <memory>
#include <network/packets/listener/PacketExecutor.hpp>
#include <network/packets/impl/PlayerIdPacket.hpp>

class PlayerIdExecutor : public PacketExecutorImplClient
<PlayerIdPacket, ClientPollable>
{
public:
    PlayerIdExecutor(Game &state) : state(state) {}

    bool execute([[maybe_unused]]Client &cl,
                 [[maybe_unused]] std::shared_ptr<ClientPollable> con,
                 [[maybe_unused]] std::shared_ptr<PlayerIdPacket> packet)
    {
        this->state.registerClientId(packet->getId());
        return true;
    }

    int getPacketId() const {
        return PacketId::PLAYER_ID;
    }
private:
    [[maybe_unused]] Game &state;
};

#endif /* PLAYERID_EXECUTOR_HPP */
