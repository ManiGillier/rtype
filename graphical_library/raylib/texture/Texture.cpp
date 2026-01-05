/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** raylib texture
*/

#include "Texture.hpp"

auto Texture::load(std::filesystem::path path) -> void
{
    this->texture = raylib::LoadTexture(path.c_str());
}

auto Texture::unload() -> void
{
    raylib::UnloadTexture(this->texture);
    this->texture = raylib::Texture2D();
}

auto Texture::draw(gl::WorldPosition position, gl::Rotation rotation,
                   gl::Scale scale) -> void
{
    raylib::DrawTextureEx(this->texture,
                          {position.x, position.y},
                          rotation,
                          scale,
                          raylib::WHITE);
}
