/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** NewPlayer executor
*/

#ifndef NEWPLAYER_EXECUTOR_HPP
#define NEWPLAYER_EXECUTOR_HPP

#include "client/state_machine/states/game/Game.hpp"

#include <iostream>
#include <memory>
#include <network/packets/listener/PacketExecutor.hpp>
#include <network/packets/impl/NewPlayerPacket.hpp>

class NewPlayerExecutor : public PacketExecutorImplClient
<NewPlayerPacket, ClientPollable>
{
public:
    NewPlayerExecutor(Game &state) : state(state) {}

    bool execute([[maybe_unused]] Client &cl,
                 [[maybe_unused]] std::shared_ptr<ClientPollable> con,
                 [[maybe_unused]] std::shared_ptr<NewPlayerPacket> packet)
    {
        this->state.newPlayer(packet->getPlayerId(), packet->getLaserId());
        return true;
    }

    int getPacketId() const {
        return PacketId::NEW_PLAYER;
    }
private:
    [[maybe_unused]] Game &state;
};

#endif /* NEWPLAYER_EXECUTOR_HPP */
