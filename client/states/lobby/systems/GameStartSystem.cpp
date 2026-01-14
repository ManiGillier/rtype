/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** game start system
*/

#include "ecs/regisrty/Registry.hpp"

#include "client/manager/NetworkManager.hpp"

#include "network/packets/impl/StartGamePacket.hpp"
#include <network/packets/impl/RegisterPacket.hpp>

#include <memory>
#include <raylib.h>

auto gameStart([[maybe_unused]] Registry &r, NetworkManager &networkManager)
{
    if (IsKeyPressed(KEY_SPACE)) {
        // std::shared_ptr<Packet> p = std::make_shared<StartGamePacket>();
        std::shared_ptr<Packet> p = create_packet(RegisterPacket, "sex", "yay");
        networkManager.sendPacket(p);
    }
}
