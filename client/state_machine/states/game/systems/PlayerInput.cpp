/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** manage player inputs
*/

#include <ecs/regisrty/Registry.hpp>
#include "client/manager/NetworkManager.hpp"
#include "../Game.hpp"
#include <network/packets/impl/ClientInputsPacket.hpp>
#include <graphical_library/api/GraphicalLibrary.hpp>

auto playerInputs([[maybe_unused]] Registry &r, gl::GraphicalLibrary &gl,
                  NetworkManager &networkManager, Game &game)
-> void
{
    ClientInputs clientInputs = {0};

    clientInputs.value.left = gl.isEventActive("move_left");
    clientInputs.value.right = gl.isEventActive("move_right");
    clientInputs.value.up = gl.isEventActive("move_up");
    clientInputs.value.down = gl.isEventActive("move_down");
    clientInputs.value.shoot = gl.isEventActive("shoot");

    if (clientInputs.byte == game.getLastClientInputs().byte)
        return;
    if (gl.isEventStart("shoot"))
        gl.play(gl.getSound("laser"));

    game.setLastClientInputs(clientInputs);
    networkManager
        .sendPacket(std::make_shared<ClientInputsPacket>(clientInputs));
}
