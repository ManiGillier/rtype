/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** graphical lib vectors
*/

#ifndef CLIENT_GRAPHICAL_LIBRARY_VECTOR_HPP
#define CLIENT_GRAPHICAL_LIBRARY_VECTOR_HPP

#include <cstdint>

namespace gl {
    struct Vector2f {
        float x;
        float y;
    };

    struct Vector2ui {
        std::uint32_t x;
        std::uint32_t y;
    };

    struct Vector2i {
        std::int32_t x;
        std::int32_t y;
    };

    typedef Vector2f WorldPosition;
    typedef Vector2i WindowPosition;
}

#endif /* CLIENT_GRAPHICAL_LIBRARY_VECTOR_HPP */
