/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** render system list
*/

#ifndef RENDER_SYSTEMS_HPP
#define RENDER_SYSTEMS_HPP

#include "ecs/regisrty/Registry.hpp"

#include "client/manager/TextureManager.hpp"

#include "shared/components/Position.hpp"
#include "shared/components/HitBox.hpp"
#include "client/components/Color.hpp"
#include "client/components/HorizontalTiling.hpp"
#include "client/components/Texture.hpp"
#include "shared/components/Laser.hpp"
#include "shared/components/Dependence.hpp"
#include <unordered_map>

/* LOGIC SYSTEMS */

/* RENDER SYSTEMS */

auto renderSquare([[maybe_unused]] Registry &reg,
    containers::indexed_zipper<SparseArray<Position>,
                               SparseArray<HitBox>,
                               SparseArray<ElementColor>> zip)
-> void;

auto renderLaser([[maybe_unused]] Registry &reg,
    containers::indexed_zipper<SparseArray<Laser>,
                               SparseArray<Dependence>,
                               SparseArray<ElementColor>> zip)
-> void;

auto animateTiling([[maybe_unused]] Registry &r,
    containers::indexed_zipper<SparseArray<HorizontalTiling>,
                               SparseArray<TextureComp>> zip,
    TextureManager &manager)
-> void;

auto renderHTiledTexture([[maybe_unused]] Registry &r,
    containers::indexed_zipper<SparseArray<HorizontalTiling>,
                               SparseArray<TextureComp>> zip,
    TextureManager &manager)
-> void;

#endif /* RENDER_SYSTEMS_HPP */
