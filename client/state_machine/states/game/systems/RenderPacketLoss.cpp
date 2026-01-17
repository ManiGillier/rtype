/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** render packet loss in game
*/

#include "../Game.hpp"
#include <string>

auto renderPacketLoss([[maybe_unused]] Registry &r,
    gl::GraphicalLibrary &gl,
    NetworkManager &nm
) -> void
{
    double const PACKET_LOSSAGE = nm.getPacketLoss();

    gl::Text text = {
        .text = std::to_string(PACKET_LOSSAGE) + "%",
        .pos =  { 1000, 30 },
        .charSize = 50,
        .color = gl::WHITE
    };

    gl.draw(text);
}
