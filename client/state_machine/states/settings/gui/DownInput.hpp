/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** test lobby button
*/

#ifndef DOWN_INPUT_HPP
#define DOWN_INPUT_HPP

#include "graphical_library/raylib/keybindSelect/KeybindSelect.hpp"
#include <iostream>

class DownInput : public KeybindSelect
{
public:
    DownInput()
    : KeybindSelect()
    {
        this->x = 1250;
        this->y = 490;
        this->width = 100;
        this->height = 100;
        this->idleColor = {200, 200, 200, 255};
        this->selectedColor = {250, 250, 250, 255};
        this->textColor = {0, 0, 0, 255};

    }

    auto onClick() -> void
    {
        std::cerr << "Just clicked the button !" << std::endl;
    }
};

#endif /* DOWN_INPUT_HPP */
