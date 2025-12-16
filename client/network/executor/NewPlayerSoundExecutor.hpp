/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** NewPlayer executor
*/

#ifndef NEWPLAYER_EXECUTOR_HPP
#define NEWPLAYER_EXECUTOR_HPP

#include "client/manager/SoundManager.hpp"

#include <memory>
#include <network/packets/listener/PacketExecutor.hpp>
#include <network/packets/impl/NewPlayerPacket.hpp>
#include <network/client/Client.hpp>

class NewPlayerSoundExecutor : public PacketExecutorImplClient
<NewPlayerPacket, ClientPollable>
{
public:
    NewPlayerSoundExecutor(SoundManager &sm) : soundManager(sm) {}

    bool execute([[maybe_unused]]Client &cl,
                 [[maybe_unused]] std::shared_ptr<ClientPollable> con,
                 [[maybe_unused]] std::shared_ptr<NewPlayerPacket> packet)
    {
        this->soundManager.playSound("client/assets/new_player.mp3");
        return true;
    }

    int getPacketId() const {
        return PacketId::NEW_PLAYER;
    }
private:
    [[maybe_unused]] SoundManager &soundManager;
};

#endif /* NEWPLAYER_EXECUTOR_HPP */
