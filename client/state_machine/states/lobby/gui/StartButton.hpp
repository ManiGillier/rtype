/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** test lobby button
*/

#ifndef START_BUTTON_HPP
#define START_BUTTON_HPP

#include <graphical_library/raylib/buttons/Button.hpp>
#include <iostream>

class StartButton
: public Button
{
public:
    StartButton
    ()
    : Button()
    {
        this->x = 720;
        this->y = 650;
        this->width = 160;
        this->height = 60;
        this->idleColor = {0, 200, 0, 255};
        this->hoverColor = {0, 255, 0, 255};
        this->pressedColor = {0, 150, 0, 255};
        this->text = "START GAME";
    }

    auto onClick() -> void
    {
        std::cerr << "Just clicked the button !" << std::endl;
    }
};

#endif /* START_BUTTON_HPP */
