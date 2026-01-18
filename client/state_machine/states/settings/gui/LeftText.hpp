/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** loggin button
*/

#ifndef LEFTTEXT_HPP
#define LEFTTEXT_HPP

#include <graphical_library/raylib/textbox/TextBox.hpp>
#include <iostream>

class LeftText : public TextBox
{
public:
    LeftText()
    : TextBox()
    {
        this->y = 190;
        this->x = 950;
        this->width = 300;
        this->height = 100;
        this->color = {200, 200, 200, 255};
        this->text = "Move Left";
        this->cColor = {0,0,0,255};
        this->alignment = LEFT;
    }
};

#endif /* LEFTTEXT_HPP */
