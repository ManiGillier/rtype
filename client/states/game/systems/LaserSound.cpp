/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** laser sound system
*/

#include "ecs/regisrty/Registry.hpp"

#include "client/manager/SoundManager.hpp"

#include <raylib.h>

auto laserSound([[maybe_unused]] Registry &r, SoundManager &soundManager)
-> void
{
    if (IsKeyPressed(KEY_SPACE)) {
        soundManager.playSound("client/assets/laser.mp3");
    }
}
