/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** graphical library texture
*/

#ifndef CLIENT_GRAPHICAL_LIBRARY_TEXTURE_HPP
#define CLIENT_GRAPHICAL_LIBRARY_TEXTURE_HPP

#include <filesystem>
#include "Vector.hpp"

namespace gl {
    class Texture {
    public:
        virtual ~Texture() = default;

        virtual auto load(std::filesystem::path) -> void = 0;
        virtual auto unload() -> void = 0;

        virtual auto draw(gl::WorldPosition, gl::Scale, gl::Rotation)
            -> void = 0;
    };
}

#endif /* CLIENT_GRAPHICAL_LIBRARY_TEXTURE_HPP */
