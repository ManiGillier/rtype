/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** raylib button
*/

#include "Button.hpp"
namespace raylib {
    #include <raylib.h>
}

Button::Button() : gl::Button() {}

void Button::draw() const {
    raylib::Rectangle buttonRect = {
        static_cast<float>(this->x),
        static_cast<float>(this->y),
        static_cast<float>(this->width),
        static_cast<float>(this->height)
    };
    gl::Color color = this->clicked ? this->pressedColor
        : this->hovered ? this->hoverColor : this->idleColor;
    raylib::Color rcolor = { color.r, color.g, color.b, color.a };
    DrawRectangleRec(buttonRect, rcolor);
    DrawRectangleLinesEx(buttonRect, 2, raylib::BLACK);

    raylib::Color rTextColor = {
        this->textColor.r, 
        this->textColor.g,
        this->textColor.b,
        this->textColor.a
    };

    DrawText(
        this->text.c_str(),
        this->x + 10,
        this->y + (this->height / 2) - 10,
        20,
        rTextColor
    );
}

void Button::update() {
    int mouseX = raylib::GetMouseX();
    int mouseY = raylib::GetMouseY();

    bool overButton = this->x < mouseX && this->x + this->width > mouseX
        && this->y < mouseY && this->y + this->height > mouseY;
    bool pressed = raylib::IsMouseButtonPressed(raylib::MOUSE_BUTTON_LEFT);
    bool released = raylib::IsMouseButtonReleased(raylib::MOUSE_BUTTON_LEFT);
    bool wasHovered = this->hovered;

    this->hovered = overButton;
    this->clicked = this->clicked && !released;
    this->clicked = this->clicked || (this->hovered && pressed);
    if (this->hovered && !wasHovered)
        this->onHover();
    if (this->clicked && pressed)
        this->onClick();
}
