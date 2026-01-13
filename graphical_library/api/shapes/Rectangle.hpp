/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** graphical library shape rect
*/

#ifndef CLIENT_GRAPHICAL_LIBRARY_SHAPE_RECT_HPP
#define CLIENT_GRAPHICAL_LIBRARY_SHAPE_RECT_HPP

#include "../Vector.hpp"
#include "../Color.hpp"

namespace gl {
    struct Rectangle {
        WorldPosition position;
        Vector2ui size;
        Color color;
    };
}

#endif /* CLIENT_GRAPHICAL_LIBRARY_SHAPE_RECT_HPP */
