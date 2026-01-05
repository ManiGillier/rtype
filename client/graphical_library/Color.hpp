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

    struct Color {
        /*Color(byte l, byte a = 255)
        : r(l), g(l), b(l), a(a) {}
        Color(byte r, byte g, byte b, byte a = 255)
        : r(r), g(g), b(b), a(a) {}*/

        byte r;
        byte g;
        byte b;
        byte a;
    };

    inline Color const BLACK {0, 0, 0, 255};
    inline Color const WHITE {255, 255, 255, 255};
    inline Color const RED {255, 0, 0, 255};
    inline Color const GREEN {0, 255, 0, 255};
    inline Color const BLUE {0, 0, 255, 255};
    inline Color const YELLOW {255, 255, 0, 255};
    inline Color const MAGENTA {255, 0, 255, 255};
    inline Color const CYAN {0, 255, 255, 255};
}

#endif /* CLIENT_GRAPHICAL_LIB_COLOR_HPP */
