/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** graphical lib interface
*/

#ifndef GRAPHICAL_LIB_INTERFACE_HPP
#define GRAPHICAL_LIB_INTERFACE_HPP

#include "api/IGameState.hpp"
#include "ecs/regisrty/Registry.hpp"

class GraphicalLibAPI
{
public:
    virtual ~GraphicalLibAPI() = default;

    virtual auto updateGameState(IGameState *) -> void = 0;
};

#endif /* GRAPHICAL_LIB_INTERFACE_HPP */
