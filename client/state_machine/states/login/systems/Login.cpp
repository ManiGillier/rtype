/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** login system
*/

#include "ecs/regisrty/Registry.hpp"

#include "client/manager/NetworkManager.hpp"

#include <network/packets/impl/StartGamePacket.hpp>
#include <network/packets/impl/RegisterPacket.hpp>
#include <network/packets/impl/LoginPacket.hpp>

#include <graphical_library/api/GraphicalLibrary.hpp>

#include <memory>

auto login([[maybe_unused]] Registry &r, gl::GraphicalLibrary &gl,
               NetworkManager &networkManager)
{
    if (gl.isEventStart("move_left")) {
        std::shared_ptr<Packet> p = std::make_shared<RegisterPacket>("jaimela", "teub");
        networkManager.sendPacket(p);
    }
    if (gl.isEventStart("move_right")) {
        std::shared_ptr<Packet> p = std::make_shared<LoginPacket>("jaimela", "teub");
        networkManager.sendPacket(p);
    }
    if (gl.isEventStart("move_up")) {
        std::shared_ptr<Packet> p = std::make_shared<RegisterPacket>("jaimele", "zgeg");
        networkManager.sendPacket(p);
    }
    if (gl.isEventStart("move_down")) {
        std::shared_ptr<Packet> p = std::make_shared<LoginPacket>("jaimele", "zgeg");
        networkManager.sendPacket(p);
    }
}
