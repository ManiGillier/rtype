/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** graphical library sound
*/

#ifndef CLIENT_GRAPHICAL_LIBRARY_SOUND_HPP
#define CLIENT_GRAPHICAL_LIBRARY_SOUND_HPP

#include <filesystem>

namespace gl {
    class Sound {
    public:
        virtual ~Sound() = default;

        virtual auto load(std::filesystem::path) -> void = 0;
        virtual auto unload() -> void = 0;

        virtual auto play() -> void = 0;
    };
}

#endif /* CLIENT_GRAPHICAL_LIBRARY_SOUND_HPP */
