/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** EnemyDied executor
*/

#ifndef ENEMYDIED_EXECUTOR_HPP
#define ENEMYDIED_EXECUTOR_HPP

#include "client/state_machine/states/game/Game.hpp"

#include <memory>
#include <network/packets/listener/PacketExecutor.hpp>
#include <network/packets/impl/EnemyDiedPacket.hpp>

class EnemyDiedExecutor : public PacketExecutorImplClient
<EnemyDiedPacket, ClientPollable>
{
public:
    EnemyDiedExecutor(Game &state) : state(state) {}

    bool execute([[maybe_unused]]Client &cl,
                 [[maybe_unused]] std::shared_ptr<ClientPollable> con,
                 [[maybe_unused]] std::shared_ptr<EnemyDiedPacket> packet)
    {
        this->state.despawnEntity(packet->getEnemyId());
        return true;
    }

    int getPacketId() const {
        return PacketId::ENEMY_DIED;
    }
private:
    [[maybe_unused]] Game &state;
};

#endif /* ENEMYDIED_EXECUTOR_HPP */
