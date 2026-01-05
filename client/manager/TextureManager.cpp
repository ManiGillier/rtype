/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** texture manager
*/

#include "TextureManager.hpp"
#include <iostream>
#include <memory>

#include <graphical_library/raylib/texture/Texture.hpp>

TextureManager::~TextureManager()
{
    this->unloadTextures();
}

auto TextureManager::registerTexture(const std::string &texturePath) -> void
{
    this->toLoad.push_back(texturePath);
}

auto TextureManager::loadTextures() -> void
{
    for (std::string path : this->toLoad) {
        if (this->textures.contains(path))
            continue;
        this->textures.emplace(path, std::make_unique<Texture>());
        this->textures.at(path)->load(path);
    }
    this->toLoad.clear();
}

auto TextureManager::unloadTextures() -> void
{
    for (auto &[_, texture] : this->textures)
        texture->unload();
    this->textures.clear();
}

auto TextureManager::getTexture(const std::string &texturePath)
    -> gl::Texture &
{
    return *this->textures.at(texturePath);
}
