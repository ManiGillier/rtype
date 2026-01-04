/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** client texture manager
*/

#ifndef CLIENT_TEXTURE_MANAGER_HPP
#define CLIENT_TEXTURE_MANAGER_HPP

#include <map>
#include <string>

#include <raylib.h>
#include <vector>

class TextureManager {
public:
    ~TextureManager();

    auto registerTexture(const std::string &texturePath) -> void;

    // May take some time
    auto loadTextures() -> void;
    auto unloadTextures() -> void;

    auto getTexture(const std::string &texturePath) -> Texture2D &;
private:
    std::vector<std::string> toLoad;
    std::map<std::string, Texture2D> textures;
};

#endif /* CLIENT_TEXTURE_MANAGER_HPP */
