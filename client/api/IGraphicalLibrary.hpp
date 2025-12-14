/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** IGraphicalLibrary
*/

#ifndef GRAPHICAL_LIBRARY_INTERFACE_HPP
#define GRAPHICAL_LIBRARY_INTERFACE_HPP

#include "IGameState.hpp"

class IGraphicalLibrary
{
public:
    virtual ~IGraphicalLibrary() = default;

    virtual auto isStopped() -> bool = 0;
    virtual auto render(IGameState &) -> void = 0;
};

#endif /* GRAPHICAL_LIBRARY_INTERFACE_HPP */
