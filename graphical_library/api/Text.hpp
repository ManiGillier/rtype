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
#include <string>

namespace gl {
    struct Text {
        std::string text;
        Vector2i pos;
        int charSize;
        Color color;
    };
}

#endif /* CLIENT_GRAPHICAL_LIBRARY_TEXT_HPP */
