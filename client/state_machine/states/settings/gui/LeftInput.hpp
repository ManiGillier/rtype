/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** test lobby button
*/

#ifndef LEFT_INPUT_HPP
#define LEFT_INPUT_HPP

#include "graphical_library/raylib/keybindSelect/KeybindSelect.hpp"
#include <iostream>

class LeftInput : public KeybindSelect
{
public:
    LeftInput(gl::GraphicalLibrary &gl)
    : KeybindSelect(gl)
    {
        this->x = 1250;
        this->y = 190;
        this->width = 100;
        this->height = 100;
        this->idleColor = {200, 200, 200, 255};
        this->selectedColor = {250, 250, 250, 255};
        this->textColor = {0, 0, 0, 255};

        this->keybind = "move_left";
    }
};

#endif /* LEFT_INPUT_HPP */
