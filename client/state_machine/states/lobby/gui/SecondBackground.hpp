/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** test lobby button
*/

#ifndef SECOND_BACKGROUND_HPP
#define SECOND_BACKGROUND_HPP

#include <graphical_library/raylib/buttons/Button.hpp>
#include <iostream>

class SecondBackground : public Button
{
public:
    SecondBackground()
    : Button()
    {
        this->x = 175;
        this->y = 500;
        this->width = 300;
        this->height = 120;
        this->idleColor = {150, 150, 150, 255};
        this->hoverColor = {150, 150, 150, 255};
        this->pressedColor = {150, 150, 150, 255};
        this->text = "";
    }
};

#endif /* SECOND_BACKGROUND_HPP */
