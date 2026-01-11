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
    struct Sound {
        std::filesystem::path path;
        std::string name;
    };
}

#endif /* CLIENT_GRAPHICAL_LIBRARY_SOUND_HPP */
