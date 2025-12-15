/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** texture manager
*/

#include "TextureManager.hpp"

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
    for (const std::string &path : this->toLoad) {
        if (this->textures.contains(path))
            continue;
        this->textures.emplace(path, LoadTexture(path.c_str()));
    }
    this->toLoad.clear();
}

auto TextureManager::unloadTextures() -> void
{
    for (auto &[_, texture] : this->textures)
        UnloadTexture(texture);
    this->textures.clear();
}

auto TextureManager::getTexture(const std::string &texturePath)
    -> Texture2D &
{
    return this->textures.at(texturePath);
}
