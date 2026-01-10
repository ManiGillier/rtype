/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** client connecting state
*/

#include "Connecting.hpp"
#include "systems/Systems.hpp"
#include "client/network/executor/AuthentifiedPacketExecutor.hpp"
#include <memory>

Connecting::Connecting(ClientManager &cm, Registry &r)
    : State(cm, r)
{}

auto Connecting::init_systems() -> void
{
    this->registry.reset_update_systems();
    this->registry.reset_render_systems();
    this->clientManager.getNetworkManager().resetExecutors();

    this->registry.add_global_render_system
        (connectingText, std::ref(this->clientManager.getGui()));
    this->clientManager.getNetworkManager()
        .addExecutor(std::make_unique<AuthentifiedPacketExecutor>
                         (std::ref(*this)));
}

auto Connecting::init_entities() -> void
{}
