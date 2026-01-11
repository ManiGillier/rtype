/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** raylib
*/

#ifndef RAYLIB_H_
#define RAYLIB_H_

#include <filesystem>
#include <graphical_library/api/GraphicalLibrary.hpp>
#include <queue>
#include <map>
#include <string>
#include <utility>

namespace raylib {
    #include <raylib.h>
}

class Raylib : public gl::GraphicalLibrary
{
public:
    auto init() -> void;
    auto deinit() -> void;

    auto should_close() -> bool;

    auto start_new_frame(gl::Color color = gl::BLACK) -> void;
    auto end_frame() -> void;

    auto draw(gl::Rectangle rect) -> void;
    auto draw(gl::Text text) -> void;
    auto draw(gl::Texture texture) -> void;

    auto getTextWidth(gl::Text text) -> int;
    auto getTextWidth(const std::string &txt, int fontSize) -> int;


    auto registerTexture(std::filesystem::path, std::string) -> void;
    auto loadAllTextures() -> void;
    auto loadTexture(std::filesystem::path, std::string) -> gl::Texture;
    auto getTexture(std::string) -> gl::Texture;

    auto registerSound(std::filesystem::path, std::string) -> void;
    auto loadAllSounds() -> void;
    auto loadSound(std::filesystem::path, std::string) -> gl::Sound;
    auto getSound(std::string) -> gl::Sound;
    auto play(gl::Sound) -> void;

    auto loadEverything() -> void;
private:
    std::queue<std::pair<std::string, std::filesystem::path>> texturesToLoad;
    std::map<std::string, std::pair<gl::Texture, raylib::Texture>> textures;

    std::queue<std::pair<std::string, std::filesystem::path>> soundsToLoad;
    std::map<std::string, std::pair<gl::Sound, raylib::Sound>> sounds;
};

#endif // RAYLIB_H_
