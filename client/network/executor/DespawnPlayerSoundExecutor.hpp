/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** DespawnPlayer executor
*/

#ifndef DESPAWNPLAYER_EXECUTOR_HPP
#define DESPAWNPLAYER_EXECUTOR_HPP

#include "client/manager/SoundManager.hpp"

#include <memory>
#include <network/packets/listener/PacketExecutor.hpp>
#include <network/packets/impl/DespawnPlayerPacket.hpp>
#include <network/client/Client.hpp>

class DespawnPlayerSoundExecutor : public PacketExecutorImplClient
<DespawnPlayerPacket, ClientPollable>
{
public:
    DespawnPlayerSoundExecutor(SoundManager &sm) : soundManager(sm) {}

    bool execute([[maybe_unused]]Client &cl,
                 [[maybe_unused]] std::shared_ptr<ClientPollable> con,
                 [[maybe_unused]] std::shared_ptr<DespawnPlayerPacket> packet)
    {
        this->soundManager.playSound("client/assets/despawn_player.mp3");
        return true;
    }

    int getPacketId() const {
        return PacketId::DESPAWN_PLAYER;
    }
private:
    [[maybe_unused]] SoundManager &soundManager;
};

#endif /* DESPAWNPLAYER_EXECUTOR_HPP */
