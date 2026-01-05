/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** render laser
*/

#include "client/graphical_library/GraphicalLibrary.hpp"

#include "ecs/regisrty/Registry.hpp"

#include "Systems.hpp"


#include <raylib.h>


auto renderLaser([[maybe_unused]] Registry &reg,
    containers::indexed_zipper<SparseArray<Laser>,
                               SparseArray<Dependence>,
                               SparseArray<ElementColor>> zip,
                 gl::GraphicalLibrary &gl)
-> void
{
    int height = GetRenderHeight();
    for (auto &&[_, laser, ref, color] : zip) {
        std::optional<Position> player_pos = reg.get<Position>(ref->id);

        if (!player_pos)
            continue;
        if (!laser->active)
            continue;
        int const laser_width = 5;
        
        gl.draw(gl::Rectangle {
            gl::WorldPosition {
                (player_pos->x - (float) laser_width / 2),
                (float) (height - (int) player_pos->y - (int) laser->length)
            },
            gl::Vector2ui {
                (std::uint32_t) laser_width,
                (std::uint32_t) laser->length
            },
            color->color
        });
    }
}
