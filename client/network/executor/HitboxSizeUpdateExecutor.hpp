/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** HitboxSizeUpdate executor
*/

#ifndef HITBOXSIZEUPDATE_EXECUTOR_HPP
#define HITBOXSIZEUPDATE_EXECUTOR_HPP

#include "client/state_machine/states/game/Game.hpp"

#include <memory>
#include <network/packets/listener/PacketExecutor.hpp>
#include <network/packets/impl/HitboxSizeUpdatePacket.hpp>

class HitboxSizeUpdateExecutor : public PacketExecutorImplClient
<HitboxSizeUpdatePacket, ClientPollable>
{
public:
    HitboxSizeUpdateExecutor(Game &state) : state(state) {}

    bool execute([[maybe_unused]]Client &cl,
                 [[maybe_unused]] std::shared_ptr<ClientPollable> con,
                 [[maybe_unused]] std::shared_ptr<HitboxSizeUpdatePacket> packet)
    {
        this->state.updateHitbox(packet->getEntityId(), packet->getWidth(),
                                 packet->getHeight());
        return true;
    }

    int getPacketId() const {
        return PacketId::HITBOX_SIZE_UPDATE;
    }
private:
    [[maybe_unused]] Game &state;
};

#endif /* HITBOXSIZEUPDATE_EXECUTOR_HPP */
