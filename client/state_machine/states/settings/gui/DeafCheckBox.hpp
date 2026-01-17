/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** deaf mode button
*/

#ifndef DEAF_HPP
#define DEAF_HPP

#include "graphical_library/api/Color.hpp"
#include <graphical_library/raylib/checkbox/Checkbox.hpp>
// #include <iostream>

class DeafMode : public Checkbox
{
public:
    DeafMode()
    : Checkbox()
    {
        this->x = 100;
        this->y = 530;
        this->text = "Deaf Mode";
        this->idleColor = {200, 0, 0, 255};
        this->hoverColor = {150, 0, 0, 255};
        this->pressedColor =  {200, 200, 0, 200};
        this->checkedColor = {0, 200, 0, 255};
        this->textColor = {255, 255, 255, 255};
        this->size = 75;
    }
};

#endif /* DEAF_HPP */
