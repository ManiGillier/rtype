/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** test lobby button
*/

#ifndef UP_INPUT_HPP
#define UP_INPUT_HPP

#include "graphical_library/raylib/keybindSelect/KeybindSelect.hpp"
#include <iostream>

class UpInput : public KeybindSelect
{
public:
    UpInput()
    : KeybindSelect()
    {
        this->x = 1250;
        this->y = 40;
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

#endif /* UP_INPUT_HPP */
