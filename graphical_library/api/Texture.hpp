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

        virtual auto draw(gl::WorldPosition, gl::Rotation = 0.0,
                          gl::Scale = 1.0) -> void = 0;

        virtual auto getWidth() const -> std::uint32_t = 0;
        virtual auto getHeight() const -> std::uint32_t = 0;
    };
}

#endif /* CLIENT_GRAPHICAL_LIBRARY_TEXTURE_HPP */
