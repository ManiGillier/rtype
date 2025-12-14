/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** placeholder executor
*/

#ifndef PLACEHOLDER_EXECUTOR_HPP
#define PLACEHOLDER_EXECUTOR_HPP

#include "client/manager/ClientManager.hpp"

#include <memory>
#include <network/packets/listener/PacketExecutor.hpp>
#include <network/packets/impl/PlaceholderPacket.hpp>

class PlaceholderExecutor : public PacketExecutorImplClient
<PlaceholderPacket, ClientPollable>
{
public:
    PlaceholderExecutor(ClientManager &cm) : clientManager(cm) {}

    bool execute([[maybe_unused]]Client &cl,
                 [[maybe_unused]] std::shared_ptr<ClientPollable> &con,
                 [[maybe_unused]] std::shared_ptr<PlaceholderPacket> packet)
    {
        return true;
    }

    int getPacketId() const {
        return PacketId::PLACEHOLDER;
    }
private:
    [[maybe_unused]] ClientManager &clientManager;
};

#endif /* PLACEHOLDER_EXECUTOR_HPP */
