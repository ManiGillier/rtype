/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** render PlayerId
*/

#include "ecs/regisrty/Registry.hpp"

#include "shared/components/Position.hpp"
#include "shared/components/HitBox.hpp"
#include "client/components/Color.hpp"
#include "client/components/PlayerId.hpp"

namespace raylib {
    #include <raylib.h>
}

#include <string>

auto renderPlayerId([[maybe_unused]] Registry &reg,
    containers::indexed_zipper<SparseArray<Position>,
                               SparseArray<PlayerId>> zip,
                    gl::GraphicalLibrary &gl,
                    std::optional<std::size_t> &my_id)
-> void
{
    int height = raylib::GetRenderHeight();
    for (auto &&[ecsId, pos, playerId] : zip) {
        gl::Color color = my_id ? (*my_id == ecsId ? gl::YELLOW : gl::WHITE)
                          : gl::RED;
        const int fontSize = 10;
        const std::string txt = std::to_string(playerId->id);
        gl::Text text = {
            txt,
            {
                (int) pos->x + 15,
                height - (int) pos->y - 10
            },
            fontSize,
            color
        };
        gl.draw(text);
    }
}
