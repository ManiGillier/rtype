/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** texture manager
*/

#include "TextureManager.hpp"
#include <iostream>

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
        Image img = LoadImage(path.c_str());
        float ratio = (600 / (float) img.height);
        ImageResize(&img, (int) ((float) img.width * ratio),
                    (int) ((float) img.height * ratio));
        this->textures.emplace(path, LoadTextureFromImage(img));
        UnloadImage(img);
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
