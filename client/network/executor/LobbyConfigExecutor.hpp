/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** LobbyConfig executor
*/

#ifndef LOBBYCONFIG_EXECUTOR_HPP
#define LOBBYCONFIG_EXECUTOR_HPP

#include "client/state_machine/states/lobby/Lobby.hpp"

#include <memory>
#include <network/packets/listener/PacketExecutor.hpp>
#include <network/packets/impl/LobbyConfigPacket.hpp>

class LobbyConfigExecutor : public PacketExecutorImplClient
<LobbyConfigPacket, ClientPollable>
{
public:
    LobbyConfigExecutor(Lobby &state) : state(state) {}

    bool execute([[maybe_unused]]Client &cl,
                 [[maybe_unused]] std::shared_ptr<ClientPollable> con,
                 [[maybe_unused]] std::shared_ptr<LobbyConfigPacket> packet)
    {
        this->state.setConfig(packet->getConfig());
        return true;
    }

    int getPacketId() const {
        return PacketId::LOBBY_CONFIG_PACKET;
    }
private:
    [[maybe_unused]] Lobby &state;
};

#endif /* LOBBYCONFIG_EXECUTOR_HPP */
