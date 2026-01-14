/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** StartGame executor
*/

#ifndef STARTGAME_EXECUTOR_HPP
#define STARTGAME_EXECUTOR_HPP

#include "client/state_machine/states/lobby/Lobby.hpp"
#include "client/state_machine/states/game/Game.hpp"

#include <memory>
#include <network/packets/listener/PacketExecutor.hpp>
#include <network/packets/impl/StartGamePacket.hpp>

class StartGameExecutor : public PacketExecutorImplClient
<StartGamePacket, ClientPollable>
{
public:
    StartGameExecutor(Lobby &state) : state(state) {}

    bool execute([[maybe_unused]]Client &cl,
                 [[maybe_unused]] std::shared_ptr<ClientPollable> con,
                 [[maybe_unused]] std::shared_ptr<StartGamePacket> packet)
    {
        this->state.change_state<Game>();
        return true;
    }

    int getPacketId() const {
        return PacketId::GAME_START_REQUEST;
    }
private:
    [[maybe_unused]] Lobby &state;
};

#endif /* STARTGAME_EXECUTOR_HPP */
