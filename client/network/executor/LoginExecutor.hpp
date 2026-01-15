/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** LoginResponse executor
*/

#ifndef LOGIN_RESPONSE_EXECUTOR_HPP
#define LOGIN_RESPONSE_EXECUTOR_HPP

#include "client/state_machine/states/login/Login.hpp"
#include "client/state_machine/states/menu/Menu.hpp"

#include <memory>
#include <network/packets/listener/PacketExecutor.hpp>
#include <network/packets/impl/LoginResponse.hpp>

class LoginResponseExecutor : public PacketExecutorImplClient
<LoginResponse, ClientPollable>
{
public:
    LoginResponseExecutor(Login &state) : state(state) {}

    bool execute([[maybe_unused]]Client &cl,
                 [[maybe_unused]] std::shared_ptr<ClientPollable> con,
                 [[maybe_unused]] std::shared_ptr<LoginResponse> packet)
    {
        if (!packet->isSuccesful())
            return true;
        state.change_state<Menu>();
        return true;
    }

    int getPacketId() const {
        return PacketId::LOGIN_RESPONSE_PACKET;
    }
private:
    [[maybe_unused]] Login &state;
};

#endif /* LOGIN_RESPONSE_EXECUTOR_HPP */
