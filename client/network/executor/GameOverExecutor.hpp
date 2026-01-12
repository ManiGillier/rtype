/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** GameOver executor
*/

#ifndef GAMEOVER_EXECUTOR_HPP
#define GAMEOVER_EXECUTOR_HPP

#include "client/state_machine/states/game/Game.hpp"

#include <memory>
#include <network/packets/listener/PacketExecutor.hpp>
#include <network/packets/impl/GameOverPacket.hpp>

class GameOverExecutor : public PacketExecutorImplClient
<GameOverPacket, ClientPollable>
{
public:
    GameOverExecutor(Game &state) : state(state) {}

    bool execute([[maybe_unused]]Client &cl,
                 [[maybe_unused]] std::shared_ptr<ClientPollable> con,
                 [[maybe_unused]] std::shared_ptr<GameOverPacket> packet)
    {
        // this->state.end();
        return true;
    }

    int getPacketId() const {
        return PacketId::GAME_OVER;
    }
private:
    [[maybe_unused]] Game &state;
};

#endif /* GAMEOVER_EXECUTOR_HPP */
