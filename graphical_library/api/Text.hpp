/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** client graphical library text
*/

#ifndef CLIENT_GRAPHICAL_LIBRARY_TEXT_HPP
#define CLIENT_GRAPHICAL_LIBRARY_TEXT_HPP

#include "Color.hpp"
#include "Vector.hpp"

namespace gl {
    class Text {
    public:
        virtual ~Text() = default;

        virtual auto draw(WorldPosition, Scale, Color) -> void = 0;
    };
}

#endif /* CLIENT_GRAPHICAL_LIBRARY_TEXT_HPP */
