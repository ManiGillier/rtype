/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** raylib
*/

#include "InputBox.hpp"

namespace raylib {
    #include <raylib.h>
}

InputBox::InputBox() : gl::InputBox() {}

void InputBox::draw() const {
    raylib::Rectangle boxRect = {
        static_cast<float>(this->x),
        static_cast<float>(this->y),
        static_cast<float>(this->width),
        static_cast<float>(this->height)
    };

    gl::Color color = this->selected ? this->selectedColor
        : this->idleColor;
    raylib::Color rcolor = { color.r, color.g, color.b, color.a };

    raylib::DrawRectangleRec(boxRect, rcolor);

    raylib::DrawRectangleLinesEx(boxRect, 2, raylib::BLACK);

    raylib::Color rTextColor = {
        this->textColor.r, 
        this->textColor.g,
        this->textColor.b,
        this->textColor.a
    };

    raylib::DrawText(
        this->text.c_str(),
        this->x + 10,
        this->y + (this->height / 2) - 10,
        20,
        rTextColor
    );
}

void InputBox::update()
{
    int mouseX = raylib::GetMouseX();
    int mouseY = raylib::GetMouseY();

    bool overButton = this->x < mouseX && this->x + this->width > mouseX
        && this->y < mouseY && this->y + this->height > mouseY;
    bool pressed = raylib::IsMouseButtonPressed(raylib::MOUSE_BUTTON_LEFT);

    if (overButton && pressed)
        this->selected = true;
    if (!overButton && pressed)
        this->selected = false;
    if (!this->selected)
        return;

    int key = raylib::GetCharPressed();
    bool changed = false;
    while (key > 0) {
        if (key >= 32 && key <= 125) {
            this->text += (char)key;
            changed = true;
        }
        key = raylib::GetCharPressed();
    }

    if (raylib::IsKeyPressed(raylib::KEY_BACKSPACE) && !this->text.empty()) {
        this->text.pop_back();
        changed = true;
    }

    if (changed)
        this->onTextChange();
}

std::string InputBox::getText(void) {
    return this->text;
}
