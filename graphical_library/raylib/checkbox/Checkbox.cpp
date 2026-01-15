#include "Checkbox.hpp"

namespace raylib {
    #include <raylib.h>
}

Checkbox::Checkbox() : gl::Checkbox() {}

void Checkbox::draw() const {
    raylib::Rectangle box = {
        static_cast<float>(this->x),
        static_cast<float>(this->y),
        static_cast<float>(this->size),
        static_cast<float>(this->size)
    };
    raylib::Rectangle checkRect = {
        static_cast<float>(this->x + 2),
        static_cast<float>(this->y + 2),
        static_cast<float>(this->size - 4),
        static_cast<float>(this->size - 4)
    };
    raylib::Color rBackgroundColor = {
        this->backgroundColor.r,
        this->backgroundColor.g,
        this->backgroundColor.b,
        this->backgroundColor.a
    };
    DrawRectangleRec(box, rBackgroundColor);
    DrawRectangleLinesEx(box, 2, raylib::BLACK);

    gl::Color checkColor = this->clicked ? this->pressedColor
        : this->checked ? this->checkedColor
        : this->hovered ? this->hoverColor
        : this->idleColor;
    raylib::Color rCheckColor = {
        checkColor.r, checkColor.g, checkColor.b, checkColor.a
    };

    DrawRectangleRec(checkRect, rCheckColor);
    DrawText(this->text.c_str(),
             this->x + this->size + 10,
             this->y + (this->size / 2) - 10,
             20,
             rBackgroundColor);
}

void Checkbox::update() {
    int mouseX = raylib::GetMouseX();
    int mouseY = raylib::GetMouseY();

    bool overButton = this->x < mouseX && this->x + this->size > mouseX
        && this->y < mouseY && this->y + this->size > mouseY;
    bool pressed = raylib::IsMouseButtonPressed(raylib::MOUSE_BUTTON_LEFT);
    bool released = raylib::IsMouseButtonReleased(raylib::MOUSE_BUTTON_LEFT);

    this->hovered = overButton;
    this->clicked = this->clicked && !released;
    this->clicked = this->clicked || (this->hovered && pressed);
    if (this->hovered && pressed) {
        this->checked = !this->checked;
        if (this->checked)
            this->onCheck();
        else
            this->onUncheck();
    }
}
