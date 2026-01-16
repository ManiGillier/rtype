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

static std::string keyToString(int key)
{
    switch (key) {
        case raylib::KEY_APOSTROPHE: return "APOSTROPHE";
        case raylib::KEY_COMMA: return "COMMA";
        case raylib::KEY_MINUS: return "MINUS";
        case raylib::KEY_PERIOD: return "PERIOD";
        case raylib::KEY_SLASH: return "SLASH";
        case raylib::KEY_ZERO: return "0";
        case raylib::KEY_ONE: return "1";
        case raylib::KEY_TWO: return "2";
        case raylib::KEY_THREE: return "3";
        case raylib::KEY_FOUR: return "4";
        case raylib::KEY_FIVE: return "5";
        case raylib::KEY_SIX: return "6";
        case raylib::KEY_SEVEN: return "7";
        case raylib::KEY_EIGHT: return "8";
        case raylib::KEY_NINE: return "9";
        case raylib::KEY_SEMICOLON: return "SEMICOLON";
        case raylib::KEY_EQUAL: return "EQUAL";
        case raylib::KEY_A: return "A";
        case raylib::KEY_B: return "B";
        case raylib::KEY_C: return "C";
        case raylib::KEY_D: return "D";
        case raylib::KEY_E: return "E";
        case raylib::KEY_F: return "F";
        case raylib::KEY_G: return "G";
        case raylib::KEY_H: return "H";
        case raylib::KEY_I: return "I";
        case raylib::KEY_J: return "J";
        case raylib::KEY_K: return "K";
        case raylib::KEY_L: return "L";
        case raylib::KEY_M: return "M";
        case raylib::KEY_N: return "N";
        case raylib::KEY_O: return "O";
        case raylib::KEY_P: return "P";
        case raylib::KEY_Q: return "Q";
        case raylib::KEY_R: return "R";
        case raylib::KEY_S: return "S";
        case raylib::KEY_T: return "T";
        case raylib::KEY_U: return "U";
        case raylib::KEY_V: return "V";
        case raylib::KEY_W: return "W";
        case raylib::KEY_X: return "X";
        case raylib::KEY_Y: return "Y";
        case raylib::KEY_Z: return "Z";
        case raylib::KEY_LEFT_BRACKET: return "LEFT_BRACKET";
        case raylib::KEY_BACKSLASH: return "BACKSLASH";
        case raylib::KEY_RIGHT_BRACKET: return "RIGHT_BRACKET";
        case raylib::KEY_GRAVE: return "GRAVE";
        case raylib::KEY_SPACE: return "SPACE";
        case raylib::KEY_ESCAPE: return "ESCAPE";
        case raylib::KEY_ENTER: return "ENTER";
        case raylib::KEY_TAB: return "TAB";
        case raylib::KEY_BACKSPACE: return "BACKSPACE";
        case raylib::KEY_INSERT: return "INSERT";
        case raylib::KEY_DELETE: return "DELETE";
        case raylib::KEY_RIGHT: return "RIGHT";
        case raylib::KEY_LEFT: return "LEFT";
        case raylib::KEY_DOWN: return "DOWN";
        case raylib::KEY_UP: return "UP";
        case raylib::KEY_PAGE_UP: return "PAGE_UP";
        case raylib::KEY_PAGE_DOWN: return "PAGE_DOWN";
        case raylib::KEY_HOME: return "HOME";
        case raylib::KEY_END: return "END";
        case raylib::KEY_CAPS_LOCK: return "CAPS_LOCK";
        case raylib::KEY_SCROLL_LOCK: return "SCROLL_LOCK";
        case raylib::KEY_NUM_LOCK: return "NUM_LOCK";
        case raylib::KEY_PRINT_SCREEN: return "PRINT_SCREEN";
        case raylib::KEY_PAUSE: return "PAUSE";
        default: return "UNKOWN";
    }
}

KeybindSelect::KeybindSelect() : gl::KeybindSelect() {}

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

    raylib::DrawText(
        keyToString(this->key).c_str(),
        this->x + 10,
        this->y + (this->y / 2) - 10,
        20,
        raylib::BLACK
    );
}

void KeybindSelect::update()
{
    int mouseX = raylib::GetMouseX();
    int mouseY = raylib::GetMouseY();

    bool overButton = this->x < mouseX && this->x + this->width > mouseX
        && this->y < mouseY && this->y + this->height > mouseY;
    bool pressed = raylib::IsMouseButtonPressed(raylib::MOUSE_BUTTON_LEFT);

    if (overButton && pressed)
        this->selected = true;
    if (!this->selected)
        return;

    int key = raylib::GetKeyPressed();

    if (key == 0)
        return;
    if (key == raylib::KEY_ESCAPE)
        this->selected = false;
    this->key = key;
    this->onKeybindSet();
}

int KeybindSelect::getKey(void) {
    return this->key;
}
