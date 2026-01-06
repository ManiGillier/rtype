/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** text
*/

#include "Text.hpp"

namespace raylib {
    #include <raylib.h>
}

Text::Text(const std::string &text) : text(text) {}

auto Text::draw(gl::WorldPosition pos, gl::Scale height,
                gl::Color color) -> void
{
    raylib::DrawText(this->text.c_str(), (int) pos.x, (int) pos.y, (int) height,
                     raylib::Color {color.r, color.g, color.b, color.a});
}

auto Text::size(int fontSize) -> int
{
    return raylib::MeasureText(this->text.c_str(), fontSize);
}
