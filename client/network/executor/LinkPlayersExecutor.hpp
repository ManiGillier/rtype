/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** LinkPlayers executor
*/

#ifndef LINK_PLAYERS_EXECUTOR_HPP
#define LINK_PLAYERS_EXECUTOR_HPP

#include "client/state_machine/states/game/Game.hpp"

#include <memory>
#include <network/packets/listener/PacketExecutor.hpp>
#include <network/packets/impl/LinkPlayersPacket.hpp>

class LinkPlayersExecutor : public PacketExecutorImplClient
<LinkPlayersPacket, ClientPollable>
{
public:
    LinkPlayersExecutor(Game &state) : state(state) {}

    bool execute([[maybe_unused]]Client &cl,
                 [[maybe_unused]] std::shared_ptr<ClientPollable> con,
                 [[maybe_unused]] std::shared_ptr<LinkPlayersPacket> packet)
    {
        this->state.newPlayers(packet->getLinks());
        return true;
    }

    int getPacketId() const {
        return PacketId::LINK_PLAYERS_PACKET;
    }
private:
    [[maybe_unused]] Game &state;
};

#endif /* LINK_PLAYERS_EXECUTOR_HPP */
