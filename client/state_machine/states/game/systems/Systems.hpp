/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** render system list
*/

#ifndef RENDER_SYSTEMS_HPP
#define RENDER_SYSTEMS_HPP

#include "../Game.hpp"

#include <graphical_library/api/GraphicalLibrary.hpp>

#include "ecs/regisrty/Registry.hpp"

#include "client/manager/NetworkManager.hpp"

#include "shared/components/Position.hpp"
#include "shared/components/HitBox.hpp"
#include "client/components/Color.hpp"
#include "client/components/HorizontalTiling.hpp"
#include "client/components/Texture.hpp"
#include "shared/components/Laser.hpp"
#include "shared/components/Dependence.hpp"
#include "client/components/PlayerId.hpp"
#include "client/components/StraightMoving.hpp"

#include <optional>
#include <unordered_map>

/* LOGIC SYSTEMS */

/* RENDER SYSTEMS */

auto renderSquare([[maybe_unused]] Registry &reg,
    containers::indexed_zipper<SparseArray<Position>,
                               SparseArray<HitBox>,
                               SparseArray<ElementColor>> zip,
                  gl::GraphicalLibrary &)
-> void;

auto renderLaser([[maybe_unused]] Registry &reg,
    containers::indexed_zipper<SparseArray<Laser>,
                               SparseArray<Dependence>,
                               SparseArray<ElementColor>> zip,
                 gl::GraphicalLibrary &)
-> void;

auto animateTiling([[maybe_unused]] Registry &r,
    containers::indexed_zipper<SparseArray<HorizontalTiling>,
                               SparseArray<TextureComp>> zip,
    gl::GraphicalLibrary &)
-> void;

auto renderHTiledTexture([[maybe_unused]] Registry &r,
    containers::indexed_zipper<SparseArray<HorizontalTiling>,
                               SparseArray<TextureComp>> zip,
    gl::GraphicalLibrary &)
-> void;

auto renderPlayerId([[maybe_unused]] Registry &reg,
    containers::indexed_zipper<SparseArray<Position>,
                               SparseArray<PlayerId>> zip,
                    gl::GraphicalLibrary & gl,
                    std::optional<std::size_t> &my_id)
-> void;

auto playerInputs([[maybe_unused]] Registry &r, gl::GraphicalLibrary &gl,
                  NetworkManager &networkManager, Game &game)
-> void;

auto updateStraightMoving([[maybe_unused]] Registry &reg,
    containers::indexed_zipper<SparseArray<Position>,
                               SparseArray<StraightMovingComp>> zip,
                  Game &state)
-> void;

auto renderHealth([[maybe_unused]] Registry &r,
    gl::GraphicalLibrary &gl,
    Game &game
) -> void;


auto lobbyPlayerList([[maybe_unused]] Registry &r,
                     gl::GraphicalLibrary &gl,
                     Game &game)
-> void;

#endif /* RENDER_SYSTEMS_HPP */
