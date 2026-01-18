/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** Score executor
*/

#ifndef SCORE_EXECUTOR_HPP
#define SCORE_EXECUTOR_HPP

#include "client/state_machine/states/menu/Menu.hpp"

#include <memory>
#include <network/packets/listener/PacketExecutor.hpp>
#include <network/packets/impl/ScorePacket.hpp>

class ScoreExecutor : public PacketExecutorImplClient
<ScorePacket, ClientPollable>
{
public:
    ScoreExecutor(Menu &state) : state(state) {}

    bool execute([[maybe_unused]]Client &cl,
                 [[maybe_unused]] std::shared_ptr<ClientPollable> con,
                 [[maybe_unused]] std::shared_ptr<ScorePacket> packet)
    {
        this->state.setScores(packet->getScores());
        return true;
    }

    int getPacketId() const {
        return PacketId::SCORE_PACKET;
    }
private:
    [[maybe_unused]] Menu &state;
};

#endif /* SCORE_EXECUTOR_HPP */
