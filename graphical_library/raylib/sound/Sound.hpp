/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** raylib sound
*/

#ifndef CLIENT_RAYLIB_SOUND_HPP
#define CLIENT_RAYLIB_SOUND_HPP

#include <graphical_library/api/Sound.hpp>

namespace raylib {
    #include <raylib.h>
}

class Sound : public gl::Sound {
public:
    auto load(std::filesystem::path path) -> void;
    auto unload() -> void;

    auto play() -> void;
private:
    raylib::Sound sound;
};

#endif /* CLIENT_RAYLIB_SOUND_HPP */
