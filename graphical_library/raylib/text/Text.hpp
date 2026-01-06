/*
** EPITECH PROJECT, 2026
** rtype 
** File description:
** raylib text
*/

#ifndef RAYLIB_TEXT_HPP
#define RAYLIB_TEXT_HPP

#include <graphical_library/api/Text.hpp>
#include <string>

class Text : public gl::Text {
public:
    Text(const std::string &text);

    auto draw(gl::WorldPosition pos, gl::Scale height, gl::Color color) -> void;

    auto size(int fontSize) -> int;
private:
    const std::string text;
};

#endif /* RAYLIB_TEXT_HPP */
