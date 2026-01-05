/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** raylib texture
*/

#ifndef CLIENT_RAYLIB_TEXTURE_HPP
#define CLIENT_RAYLIB_TEXTURE_HPP

#include <cstdint>
#include <filesystem>
#include <graphical_library/api/Texture.hpp>

namespace raylib {
    #include <raylib.h>
}

class Texture : public gl::Texture {
public:
    auto load(std::filesystem::path) -> void;
    auto unload() -> void;

    auto draw(gl::WorldPosition,
              gl::Rotation = 0.0,
              gl::Scale = 1.0) -> void;

    auto getWidth() const -> std::uint32_t;
    auto getHeight() const -> std::uint32_t;
private:
    raylib::Texture2D texture;
};

#endif /* CLIENT_RAYLIB_TEXTURE_HPP */
