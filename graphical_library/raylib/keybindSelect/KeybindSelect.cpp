/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** raylib
*/

#include "KeybindSelect.hpp"

namespace raylib {
    #include <raylib.h>
}

static std::string keyToString(gl::Key key)
{
    switch (key) {
    case gl::Key::UNDEFINED:
        return "<\?\?\?>";
    case gl::Key::A:
        return "A";
    case gl::Key::B:
        return "B";
    case gl::Key::C:
        return "C";
    case gl::Key::D:
        return "D";
    case gl::Key::E:
        return "E";
    case gl::Key::F:
        return "F";
    case gl::Key::G:
        return "G";
    case gl::Key::H:
        return "H";
    case gl::Key::I:
        return "I";
    case gl::Key::J:
        return "J";
    case gl::Key::K:
        return "K";
    case gl::Key::L:
        return "L";
    case gl::Key::M:
        return "M";
    case gl::Key::N:
        return "N";
    case gl::Key::O:
        return "O";
    case gl::Key::P:
        return "P";
    case gl::Key::Q:
        return "Q";
    case gl::Key::R:
        return "R";
    case gl::Key::S:
        return "S";
    case gl::Key::T:
        return "T";
    case gl::Key::U:
        return "U";
    case gl::Key::V:
        return "V";
    case gl::Key::W:
        return "W";
    case gl::Key::X:
        return "X";
    case gl::Key::Y:
        return "Y";
    case gl::Key::Z:
        return "Z";
    case gl::Key::ARROW_LEFT:
        return "LEFT";
    case gl::Key::ARROW_RIGHT:
        return "RIGHT";
    case gl::Key::ARROW_UP:
        return "UP";
    case gl::Key::ARROW_DOWN:
        return "DOWN";
    case gl::Key::ESCAPE:
        return "ESCAPE";
    case gl::Key::ENTER:
        return "ENTER";
    case gl::Key::SHIFT:
        return "SHIFT";
    case gl::Key::SPACE:
        return "SPACE";
    default:
        return "???";
    }
}

KeybindSelect::KeybindSelect(gl::GraphicalLibrary &gl)
: gl::KeybindSelect(), gl(gl) {}

void KeybindSelect::draw() const {
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
        keyToString(this->key).c_str(),
        this->x + 10,
        this->y + (this->height / 2) - 10,
        20,
        rTextColor
    );
}

void KeybindSelect::update()
{
    int mouseX = raylib::GetMouseX();
    int mouseY = raylib::GetMouseY();

    this->key = this->gl.getEventKey(this->keybind);
    bool overButton = this->x < mouseX && this->x + this->width > mouseX
        && this->y < mouseY && this->y + this->height > mouseY;
    bool pressed = raylib::IsMouseButtonPressed(raylib::MOUSE_BUTTON_LEFT);

    if (overButton && pressed)
        this->selected = true;
    if (!overButton && pressed)
        this->selected = false;
    if (!this->selected)
        return;

    int key = raylib::GetKeyPressed();

    if (key == 0)
        return;
    if (key == raylib::KEY_ESCAPE)
        this->selected = false;
    this->key = this->gl.convertKey(key);
    this->gl.bindKey(this->keybind, this->key);
    this->onKeybindSet();
}

auto KeybindSelect::getKey(void) -> gl::Key {
    return this->key;
}
