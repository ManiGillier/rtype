/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** authentified packet executor
*/

#ifndef AUTHPACKET_EXECUTOR_HPP
#define AUTHPACKET_EXECUTOR_HPP

#include "client/state_machine/states/connecting/Connecting.hpp"
#include "client/state_machine/states/lobby/Lobby.hpp"

#include <memory>
#include <network/packets/listener/PacketExecutor.hpp>
#include <network/packets/impl/AuthentifiedPacket.hpp>

class AuthentifiedPacketExecutor : public PacketExecutorImplClient
<AuthentifiedPacket, ClientPollable>
{
public:
    AuthentifiedPacketExecutor(Connecting &state) : state(state) {}

    bool execute([[maybe_unused]] Client &cl,
                 [[maybe_unused]] std::shared_ptr<ClientPollable> con,
                 [[maybe_unused]] std::shared_ptr<AuthentifiedPacket> packet)
    {
        this->state.change_state<Lobby>();
        return true;
    }

    int getPacketId() const {
        return PacketId::AUTHENTIFIED_PACKET;
    }
private:
    [[maybe_unused]] Connecting &state;
};

#endif /* STARTGAME_EXECUTOR_HPP */
