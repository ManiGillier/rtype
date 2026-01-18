/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** test lobby button
*/

#ifndef SECOND_BACKGROUND_HPP
#define SECOND_BACKGROUND_HPP

#include <graphical_library/raylib/box/Box.hpp>
#include <iostream>

class SecondBackground : public Box
{
public:
    SecondBackground()
    : Box()
    {
        this->x = 175;
        this->y = 500;
        this->width = 300;
        this->height = 120;
        this->color = {150, 150, 150, 255};
    }
};

#endif /* SECOND_BACKGROUND_HPP */
