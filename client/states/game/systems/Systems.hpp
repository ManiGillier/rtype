/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** render system list
*/

#ifndef RENDER_SYSTEMS_HPP
#define RENDER_SYSTEMS_HPP

#include "ecs/regisrty/Registry.hpp"

#include "shared/components/Position.hpp"
#include "client/components/Square.hpp"
#include <unordered_map>

/* LOGIC SYSTEMS */

/* RENDER SYSTEMS */

auto renderSquare([[maybe_unused]] Registry &reg,
    containers::indexed_zipper<SparseArray<Position>,
                               SparseArray<Square>> zip)
-> void;

#endif /* RENDER_SYSTEMS_HPP */
