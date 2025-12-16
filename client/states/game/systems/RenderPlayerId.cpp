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

#include <raylib.h>
#include <string>


auto renderPlayerId([[maybe_unused]] Registry &reg,
    containers::indexed_zipper<SparseArray<Position>,
                               SparseArray<PlayerId>> zip,
                    std::optional<std::size_t> &my_id)
-> void
{
    int height = GetRenderHeight();
    for (auto &&[ecsId, pos, playerId] : zip) {
        Color color = my_id ? (*my_id == ecsId ? YELLOW : WHITE) : RED;
        DrawText(std::to_string(playerId->id).c_str(),
                 (int) pos->x + 15, height - (int) pos->y - 10, 10, color);
/*
        DrawRectangle((int) (pos->x - (size->height / 2.0)),
                      height - (int) pos->y - (int) (size->width / 2.0),
                      (int) size->height, (int) size->width,
                      PlayerId_color->color);
*/
    }
}
