/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** sound manager
*/

#ifndef CLIENT_SOUND_MANAGER_HPP
#define CLIENT_SOUND_MANAGER_HPP

#include <map>
#include <string>

#include <raylib.h>

class SoundManager
{
public:
    SoundManager() {
        InitAudioDevice();
    }
    ~SoundManager() {
        for (auto &[_, sound] : this->sounds)
            UnloadSound(sound);
        CloseAudioDevice();
    }
    auto loadSound(std::string path) -> void {
        if (this->sounds.contains(path))
            return;
        this->sounds.emplace(path, LoadSound(path.c_str()));
    }
    auto playSound(std::string path) -> void {
        PlaySound(this->sounds.at(path));
    }
private:
    std::map<std::string, Sound> sounds;
};

#endif /* CLIENT_SOUND_MANAGER_HPP */
