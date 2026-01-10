/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** DespawnBullet executor
*/

#ifndef DESPAWNBULLET_EXECUTOR_HPP
#define DESPAWNBULLET_EXECUTOR_HPP

#include "client/state_machine/states/game/Game.hpp"

#include <memory>
#include <network/packets/listener/PacketExecutor.hpp>
#include <network/packets/impl/DespawnBulletPacket.hpp>

class DespawnBulletExecutor : public PacketExecutorImplClient
<DespawnBulletPacket, ClientPollable>
{
public:
    DespawnBulletExecutor(Game &state) : state(state) {}

    bool execute([[maybe_unused]]Client &cl,
                 [[maybe_unused]] std::shared_ptr<ClientPollable> con,
                 [[maybe_unused]] std::shared_ptr<DespawnBulletPacket> packet)
    {
        this->state.despawnEntity(packet->getBulletId());
        return true;
    }

    int getPacketId() const {
        return PacketId::DESPAWN_BULLET;
    }
private:
    [[maybe_unused]] Game &state;
};

#endif /* DESPAWNBULLET_EXECUTOR_HPP */
