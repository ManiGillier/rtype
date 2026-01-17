/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** loggin button
*/

#ifndef DIFFICULTY_HPP
#define DIFFICULTY_HPP

#include <graphical_library/raylib/textbox/TextBox.hpp>
#include <iostream>

class Difficulty : public TextBox
{
public:
    Difficulty()
    : TextBox()
    {
        this->x = 175;
        this->width = 300;
        this->y = 300;
        this->height = 40;
        this->color = {0, 0, 0, 75};
        this->text = "Difficulty";
        this->cColor = {0,0,0,255};
        this->alignment = CENTER;
    }
};

#endif /* DIFFICULTY_HPP */
