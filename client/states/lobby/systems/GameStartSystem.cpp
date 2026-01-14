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
#include <network/packets/impl/LoginPacket.hpp>

#include <memory>
#include <raylib.h>

auto gameStart([[maybe_unused]] Registry &r, NetworkManager &networkManager)
{
    if (IsKeyPressed(KEY_SPACE)) {
        std::shared_ptr<Packet> p = create_packet(LoginPacket, "sex", "yay");
        networkManager.sendPacket(p);
    }
    if (IsKeyPressed(KEY_L)) {
        std::shared_ptr<Packet> p = std::make_shared<StartGamePacket>();
        networkManager.sendPacket(p);
    }
}
