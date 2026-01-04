/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** graphical lib colors
*/

#ifndef CLIENT_GRAPHICAL_LIB_COLOR_HPP
#define CLIENT_GRAPHICAL_LIB_COLOR_HPP

#include <cstdint>

namespace gl {
    using byte = std::uint8_t;

    class Color {
    public:
        Color(byte l, byte a = 255)
        : r(l), g(l), b(l), a(a) {}
        Color(byte r, byte g, byte b, byte a = 255)
        : r(r), g(g), b(b), a(a) {}

        byte r;
        byte g;
        byte b;
        byte a;
    };

    inline Color const BLACK = Color(0, 0, 0, 255);
    inline Color const WHITE = Color(255, 255, 255, 255);
    inline Color const RED = Color(255, 0, 0, 255);
    inline Color const GREEN = Color(0, 255, 0, 255);
    inline Color const BLUE = Color(0, 0, 255, 255);
    inline Color const YELLOW = Color(255, 255, 0, 255);
    inline Color const MAGENTA = Color(255, 0, 255, 255);
    inline Color const CYAN = Color(0, 255, 255, 255);
}

#endif /* CLIENT_GRAPHICAL_LIB_COLOR_HPP */
