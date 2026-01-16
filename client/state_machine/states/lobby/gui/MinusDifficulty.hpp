/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** test lobby button
*/

#ifndef MINUS_DIFFICULTY_BUTTON_HPP
#define MINUS_DIFFICULTY_BUTTON_HPP

#include <graphical_library/raylib/buttons/Button.hpp>
#include <iostream>

class MinusDifficulty : public Button
{
public:
    MinusDifficulty()
    : Button()
    {
        this->x = 250;
        this->y = 200;
        this->width = 40;
        this->height = 40;
        this->idleColor = {100, 100, 100, 255};
        this->hoverColor = {150, 150, 150, 255};
        this->pressedColor = {70, 70, 70, 255};
        this->text = "-";
    }

    auto onClick() -> void
    {
        std::cerr << "Just clicked the button !" << std::endl;
    }
};

#endif /* MINUS_DIFFICULTY_BUTTON_HPP */
