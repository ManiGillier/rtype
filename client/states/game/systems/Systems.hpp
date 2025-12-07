/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** render system list
*/

#ifndef RENDER_SYSTEMS_HPP
#define RENDER_SYSTEMS_HPP

#include "ecs/regisrty/Registry.hpp"

#include "client/components/Position.hpp"
#include "client/components/Square.hpp"
#include "client/components/Player.hpp"
#include <unordered_map>

auto renderSquare(Registry &,
    std::unordered_map<std::size_t, std::tuple<Position*, Square*>>)
-> void;

auto movePlayer(Registry &,
    std::unordered_map<std::size_t, std::tuple<Position*, PlayerControler*>>)
-> void;

#endif /* RENDER_SYSTEMS_HPP */
