/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** GameOver executor
*/

#ifndef GAMEOVER_EXECUTOR_HPP
#define GAMEOVER_EXECUTOR_HPP

#include "client/states/game/logic.hpp"

#include <memory>
#include <network/packets/listener/PacketExecutor.hpp>
#include <network/packets/impl/GameOverPacket.hpp>

class GameOverExecutor : public PacketExecutorImplClient
<GameOverPacket, ClientPollable>
{
public:
    GameOverExecutor(InGameStateLogic &logic) : logic(logic) {}

    bool execute([[maybe_unused]]Client &cl,
                 [[maybe_unused]] std::shared_ptr<ClientPollable> &con,
                 [[maybe_unused]] std::shared_ptr<GameOverPacket> packet)
    {
        this->logic.end();
        return true;
    }

    int getPacketId() const {
        return PacketId::GAME_OVER;
    }
private:
    [[maybe_unused]] InGameStateLogic &logic;
};

#endif /* GAMEOVER_EXECUTOR_HPP */
