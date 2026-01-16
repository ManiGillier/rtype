/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** raylib
*/

#include "TextBox.hpp"

namespace raylib {
    #include <raylib.h>
}

TextBox::TextBox() : gl::TextBox() {}

void TextBox::draw() const {
    raylib::Rectangle boxRect = {
        static_cast<float>(this->x),
        static_cast<float>(this->y),
        static_cast<float>(this->width),
        static_cast<float>(this->height)
    };

    raylib::Color rcolor = {
        this->color.r,
        this->color.g,
        this->color.b,
        this->color.a
    };
    raylib::DrawRectangleRec(boxRect, rcolor);
    raylib::DrawRectangleLinesEx(boxRect, 1, raylib::BLACK);

    int fontSize = this->height / 2;
    DrawText(
        this->text.c_str(),
        this->x + 10,
        this->y + (this->height / 2) - 10,
        fontSize,
        raylib::BLACK
    );
}

void TextBox::update() {}
