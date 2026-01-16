/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** NewPlayer executor
*/

#ifndef NEWPLAYER_EXECUTOR_HPP
#define NEWPLAYER_EXECUTOR_HPP

#include "client/state_machine/states/lobby/Lobby.hpp"

#include <iostream>
#include <memory>
#include <network/packets/listener/PacketExecutor.hpp>
#include <network/packets/impl/NewPlayerPacket.hpp>

class NewPlayerExecutor : public PacketExecutorImplClient
<NewPlayerPacket, ClientPollable>
{
public:
    NewPlayerExecutor(Lobby &state) : state(state) {}

    bool execute([[maybe_unused]] Client &cl,
                 [[maybe_unused]] std::shared_ptr<ClientPollable> con,
                 [[maybe_unused]] std::shared_ptr<NewPlayerPacket> packet)
    {
        gl::Sound sound = this->state.getGraphicalLibrary()
            .getSound("new_player");

        this->state.updatePlayers(packet->getUsernames());
        this->state.getGraphicalLibrary().play(sound);
        return true;
    }

    int getPacketId() const {
        return PacketId::NEW_PLAYER;
    }
private:
    [[maybe_unused]] Lobby &state;
};

#endif /* NEWPLAYER_EXECUTOR_HPP */
