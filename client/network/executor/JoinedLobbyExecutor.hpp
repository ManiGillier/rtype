/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** JoinedLobby executor
*/

#ifndef JOINED_LOBBY_EXECUTOR_HPP
#define JOINED_LOBBY_EXECUTOR_HPP

#include "client/state_machine/states/menu/Menu.hpp"
#include "client/state_machine/states/lobby/Lobby.hpp"

#include <memory>
#include <network/packets/listener/PacketExecutor.hpp>
#include <network/packets/impl/JoinedLobbyPacket.hpp>

class JoinedLobbyExecutor : public PacketExecutorImplClient
<JoinedLobbyPacket, ClientPollable>
{
public:
    JoinedLobbyExecutor(Menu &state) : state(state) {}

    bool execute([[maybe_unused]]Client &cl,
                 [[maybe_unused]] std::shared_ptr<ClientPollable> con,
                 [[maybe_unused]] std::shared_ptr<JoinedLobbyPacket> packet)
    {
        this->state.change_state<Lobby>(packet->getCode());
        return false;
    }

    int getPacketId() const {
        return PacketId::JOINED_LOBBY_PACKET;
    }
private:
    [[maybe_unused]] Menu &state;
};

#endif /* JOINED_LOBBY_EXECUTOR_HPP */
