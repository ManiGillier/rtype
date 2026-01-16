/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** raylib
*/

#include "Box.hpp"

namespace raylib {
    #include <raylib.h>
}

Box::Box() : gl::Box() {}

void Box::draw() const {
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
}

void Box::update() {}
