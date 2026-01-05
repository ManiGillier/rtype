/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** client sound manager
*/

#include "SoundManager.hpp"

#include "client/raylib/sound/Sound.hpp"

SoundManager::~SoundManager()
{
    for (auto &[_, sound] : this->sounds) {
        sound->unload();
    }
}

auto SoundManager::loadSound(std::string path) -> void
{
    if (this->sounds.contains(path))
        return;
    this->sounds.emplace(path, std::make_unique<Sound>());
    this->sounds.at(path)->load(path);
}

auto SoundManager::playSound(std::string path) -> void
{
    this->sounds.at(path)->play();
}
