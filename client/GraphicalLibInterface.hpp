/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** graphical lib interface
*/

#ifndef GRAPHICAL_LIB_INTERFACE_HPP
#define GRAPHICAL_LIB_INTERFACE_HPP

#include "ecs/regisrty/Registry.hpp"

typedef std::size_t index_t;

class GraphicalLibAPI
{
public:
    virtual ~GraphicalLibAPI() = default;

protected:
    // Called each frame
    // Will use the registry to find all render items
    virtual auto update(const Registry &) -> void;
};

#endif /* GRAPHICAL_LIB_INTERFACE_HPP */
