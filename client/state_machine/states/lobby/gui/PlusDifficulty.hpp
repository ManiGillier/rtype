/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** test lobby button
*/

#ifndef PLUS_DIFFICULTY_BUTTON_HPP
#define PLUS_DIFFICULTY_BUTTON_HPP

#include <graphical_library/raylib/buttons/Button.hpp>
#include <iostream>

class PlusDifficulty : public Button
{
public:
    PlusDifficulty()
    : Button()
    {
        this->x = 370;
        this->y = 160;
        this->width = 40;
        this->height = 40;
        this->idleColor = {100, 100, 100, 255};
        this->hoverColor = {150, 150, 150, 255};
        this->pressedColor = {70, 70, 70, 255};
        this->text = "+";
    }

    auto onClick() -> void
    {
        std::cerr << "Just clicked the button !" << std::endl;
    }
};

#endif /* PLUS_DIFFICULTY_BUTTON_HPP */
