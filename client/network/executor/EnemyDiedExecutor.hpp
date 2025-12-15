/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** EnemyDied executor
*/

#ifndef ENEMYDIED_EXECUTOR_HPP
#define ENEMYDIED_EXECUTOR_HPP

#include "client/states/game/logic.hpp"

#include <memory>
#include <network/packets/listener/PacketExecutor.hpp>
#include <network/packets/impl/EnemyDiedPacket.hpp>

class EnemyDiedExecutor : public PacketExecutorImplClient
<EnemyDiedPacket, ClientPollable>
{
public:
    EnemyDiedExecutor(InGameStateLogic &logic) : logic(logic) {}

    bool execute([[maybe_unused]]Client &cl,
                 [[maybe_unused]] std::shared_ptr<ClientPollable> con,
                 [[maybe_unused]] std::shared_ptr<EnemyDiedPacket> packet)
    {
        this->logic.despawnEntity(packet->getEnemyId());
        return true;
    }

    int getPacketId() const {
        return PacketId::ENEMY_DIED;
    }
private:
    [[maybe_unused]] InGameStateLogic &logic;
};

#endif /* ENEMYDIED_EXECUTOR_HPP */
