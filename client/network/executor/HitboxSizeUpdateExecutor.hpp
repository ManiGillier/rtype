/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** HitboxSizeUpdate executor
*/

#ifndef HITBOXSIZEUPDATE_EXECUTOR_HPP
#define HITBOXSIZEUPDATE_EXECUTOR_HPP

#include "client/states/game/logic.hpp"

#include <memory>
#include <network/packets/listener/PacketExecutor.hpp>
#include <network/packets/impl/HitboxSizeUpdatePacket.hpp>

class HitboxSizeUpdateExecutor : public PacketExecutorImplClient
<HitboxSizeUpdatePacket, ClientPollable>
{
public:
    HitboxSizeUpdateExecutor(InGameStateLogic &logic) : logic(logic) {}

    bool execute([[maybe_unused]]Client &cl,
                 [[maybe_unused]] std::shared_ptr<ClientPollable> &con,
                 [[maybe_unused]] std::shared_ptr<HitboxSizeUpdatePacket> packet)
    {
        this->logic.updateHitbox(packet->getEntityId(), packet->getWidth(),
                                 packet->getHeight());
        return true;
    }

    int getPacketId() const {
        return PacketId::HITBOX_SIZE_UPDATE;
    }
private:
    [[maybe_unused]] InGameStateLogic &logic;
};

#endif /* HITBOXSIZEUPDATE_EXECUTOR_HPP */
