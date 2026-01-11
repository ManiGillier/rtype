/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** game start system
*/

#include "ecs/regisrty/Registry.hpp"

#include "client/manager/NetworkManager.hpp"

#include "network/packets/impl/StartGamePacket.hpp"

#include <graphical_library/api/GraphicalLibrary.hpp>

#include <memory>

auto gameStart([[maybe_unused]] Registry &r, gl::GraphicalLibrary &gl,
               NetworkManager &networkManager)
{
    if (gl.isEventStart("start_game")) {
        std::shared_ptr<Packet> p = std::make_shared<StartGamePacket>();
        networkManager.sendPacket(p);
    }
}
