/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** sound raylb
*/

#include "Sound.hpp"

auto Sound::load(std::filesystem::path path) -> void
{
    this->sound = raylib::LoadSound(path.c_str());
}

auto Sound::unload() -> void
{
    raylib::UnloadSound(this->sound);
    this->sound = raylib::Sound();
}

auto Sound::play() -> void
{
    raylib::PlaySound(this->sound);
}
