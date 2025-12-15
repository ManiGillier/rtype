/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** DespawnPlayer executor
*/

#ifndef DESPAWNPLAYER_EXECUTOR_HPP
#define DESPAWNPLAYER_EXECUTOR_HPP

#include "client/states/game/logic.hpp"

#include <memory>
#include <network/packets/listener/PacketExecutor.hpp>
#include <network/packets/impl/DespawnPlayerPacket.hpp>

class DespawnPlayerExecutor : public PacketExecutorImplClient
<DespawnPlayerPacket, ClientPollable>
{
public:
    DespawnPlayerExecutor(InGameStateLogic &logic) : logic(logic) {}

    bool execute([[maybe_unused]]Client &cl,
                 [[maybe_unused]] std::shared_ptr<ClientPollable> con,
                 [[maybe_unused]] std::shared_ptr<DespawnPlayerPacket> packet)
    {
        this->logic.despawnEntity(packet->getPlayerId());
        return true;
    }

    int getPacketId() const {
        return PacketId::DESPAWN_PLAYER;
    }
private:
    [[maybe_unused]] InGameStateLogic &logic;
};

#endif /* DESPAWNPLAYER_EXECUTOR_HPP */
