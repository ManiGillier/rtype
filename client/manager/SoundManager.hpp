/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** sound manager
*/

#ifndef CLIENT_SOUND_MANAGER_HPP
#define CLIENT_SOUND_MANAGER_HPP

#include <map>
#include <memory>
#include <string>

#include <graphical_library/api/Sound.hpp>

class SoundManager
{
public:
    ~SoundManager();

    auto loadSound(std::string path) -> void;
    auto playSound(std::string path) -> void;
private:
    std::map<std::string, std::unique_ptr<gl::Sound>> sounds;
};

#endif /* CLIENT_SOUND_MANAGER_HPP */
