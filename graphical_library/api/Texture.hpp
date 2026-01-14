/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** graphical library texture
*/

#ifndef CLIENT_GRAPHICAL_LIBRARY_TEXTURE_HPP
#define CLIENT_GRAPHICAL_LIBRARY_TEXTURE_HPP

#include <cstdint>
#include <filesystem>
#include <string>
#include "Vector.hpp"

namespace gl {
    struct Texture {
        std::filesystem::path path;
        std::string name;
        Vector2ui size;
        float scale;
        Vector2i pos;
        float rotation;
    };
}

#endif /* CLIENT_GRAPHICAL_LIBRARY_TEXTURE_HPP */
