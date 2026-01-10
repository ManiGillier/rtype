/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** manage player inputs
*/

#include <ecs/regisrty/Registry.hpp>
#include "client/manager/NetworkManager.hpp"
#include <network/packets/impl/ClientInputsPacket.hpp>

namespace raylib {
    #include <raylib.h>
}

auto playerInputs([[maybe_unused]] Registry &r, NetworkManager &networkManager)
-> void
{
    ClientInputs clientInputs = {0};

    clientInputs.value.left = IsKeyDown(raylib::KEY_LEFT)
                              || IsKeyDown(raylib::KEY_Q);
    clientInputs.value.right = IsKeyDown(raylib::KEY_RIGHT)
                               || IsKeyDown(raylib::KEY_D);
    clientInputs.value.up = IsKeyDown(raylib::KEY_UP)
                            || IsKeyDown(raylib::KEY_Z);
    clientInputs.value.down = IsKeyDown(raylib::KEY_DOWN)
                              || IsKeyDown(raylib::KEY_S);
    clientInputs.value.shoot = IsKeyDown(raylib::KEY_SPACE)
                               || IsMouseButtonDown(raylib::MOUSE_BUTTON_LEFT);

    networkManager
        .sendPacket(std::make_shared<ClientInputsPacket>(clientInputs));
}
