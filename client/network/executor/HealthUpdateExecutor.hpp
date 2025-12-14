/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** HealthUpdate executor
*/

#ifndef HEALTHUPDATE_EXECUTOR_HPP
#define HEALTHUPDATE_EXECUTOR_HPP

#include "client/states/game/logic.hpp"

#include <memory>
#include <network/packets/listener/PacketExecutor.hpp>
#include <network/packets/impl/HealthUpdatePacket.hpp>

class HealthUpdateExecutor : public PacketExecutorImplClient
<HealthUpdatePacket, ClientPollable>
{
public:
    HealthUpdateExecutor(InGameStateLogic &logic) : logic(logic) {}

    bool execute([[maybe_unused]]Client &cl,
                 [[maybe_unused]] std::shared_ptr<ClientPollable> &con,
                 [[maybe_unused]] std::shared_ptr<HealthUpdatePacket> packet)
    {
        this->logic.updateHealth(packet->getEntityId(), packet->getHealth(),
                                 packet->getMaxHealth());
        return true;
    }

    int getPacketId() const {
        return PacketId::HEALTH_UPDATE;
    }
private:
    [[maybe_unused]] InGameStateLogic &logic;
};

#endif /* HEALTHUPDATE_EXECUTOR_HPP */
