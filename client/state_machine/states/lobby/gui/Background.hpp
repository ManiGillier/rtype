/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** test lobby button
*/

#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include <graphical_library/raylib/box/Box.hpp>
#include <iostream>

class Background : public Box
{
public:
    Background()
    : Box()
    {
        this->x = 175;
        this->y = 300;
        this->width = 300;
        this->height = 120;
        this->color = {150, 150, 150, 255};
    }
};

#endif /* BACKGROUND_HPP */
