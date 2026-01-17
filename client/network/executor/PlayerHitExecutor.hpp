/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** PlayerHit executor
*/

#ifndef PLAYERHIT_EXECUTOR_HPP
#define PLAYERHIT_EXECUTOR_HPP

#include "client/state_machine/states/game/Game.hpp"

#include <memory>
#include <network/packets/listener/PacketExecutor.hpp>
#include <network/packets/impl/PlayerHitPacket.hpp>

class PlayerHitExecutor : public PacketExecutorImplClient
<PlayerHitPacket, ClientPollable>
{
public:
    PlayerHitExecutor(Game &state) : state(state) {}

    bool execute([[maybe_unused]]Client &cl,
                 [[maybe_unused]] std::shared_ptr<ClientPollable> con,
                 [[maybe_unused]] std::shared_ptr<PlayerHitPacket> packet)
    {
        this->state.hit();
        return true;
    }

    int getPacketId() const {
        return PacketId::PLAYER_HIT;
    }
private:
    [[maybe_unused]] Game &state;
};

#endif /* PLAYERHIT_EXECUTOR_HPP */
