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

    raylib::Color linesColor = {cColor.r, cColor.b, cColor.b, cColor.a};

    raylib::DrawRectangleRec(boxRect, rcolor);
    raylib::DrawRectangleLinesEx(boxRect, lineThickness, linesColor);


    raylib::Color rTextColor = {
        this->textColor.r, 
        this->textColor.g,
        this->textColor.b,
        this->textColor.a
    };

    int fontSize = this->height / 2;
    int textLenght = raylib::MeasureText(this->text.c_str(), fontSize);
    if (this->alignment == LEFT) {
    DrawText(
        this->text.c_str(),
        this->x + 10,
        this->y + (this->height / 2) - 10,
        fontSize,
        rTextColor
    );
    } else if (this->alignment == CENTER) {
        DrawText(
            this->text.c_str(),
            this->x + (this->width - textLenght) / 2,
            this->y + (this->height / 2) - 10,
            fontSize,
            raylib::BLACK
        );
    } else {
        DrawText(
            this->text.c_str(),
            this->x + (this->width - textLenght) - 10,
            this->y + (this->height / 2) - 10,
            fontSize,
            raylib::BLACK
        );
    }
}

void TextBox::update() {}
