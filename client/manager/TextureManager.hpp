/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** client texture manager
*/

#ifndef CLIENT_TEXTURE_MANAGER_HPP
#define CLIENT_TEXTURE_MANAGER_HPP

#include <map>
#include <memory>
#include <string>

#include <vector>

#include <graphical_library/api/Texture.hpp>

class TextureManager {
public:
    ~TextureManager();

    auto registerTexture(const std::string &texturePath) -> void;

    // May take some time
    auto loadTextures() -> void;
    auto unloadTextures() -> void;

    auto getTexture(const std::string &texturePath) -> gl::Texture &;
private:
    std::vector<std::string> toLoad;
    std::map<std::string, std::unique_ptr<gl::Texture>> textures;
};

#endif /* CLIENT_TEXTURE_MANAGER_HPP */
