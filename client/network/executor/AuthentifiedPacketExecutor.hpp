/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** authentified packet executor
*/

#ifndef AUTHPACKET_EXECUTOR_HPP
#define AUTHPACKET_EXECUTOR_HPP

#include "client/states/connecting/logic.hpp"

#include <memory>
#include <network/packets/listener/PacketExecutor.hpp>
#include <network/packets/impl/AuthentifiedPacket.hpp>

class AuthentifiedPacketExecutor : public PacketExecutorImplClient
<AuthentifiedPacket, ClientPollable>
{
public:
    AuthentifiedPacketExecutor(ConnectingStateLogic &logic) : logic(logic) {}

    bool execute([[maybe_unused]]Client &cl,
                 [[maybe_unused]] std::shared_ptr<ClientPollable> con,
                 [[maybe_unused]] std::shared_ptr<AuthentifiedPacket> packet)
    {
        this->logic.notifyAuthentified();
        return true;
    }

    int getPacketId() const {
        return PacketId::AUTHENTIFIED_PACKET;
    }
private:
    [[maybe_unused]] ConnectingStateLogic &logic;
};

#endif /* STARTGAME_EXECUTOR_HPP */
