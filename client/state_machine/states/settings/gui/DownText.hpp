/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** loggin button
*/

#ifndef DOWNTEXT_HPP
#define DOWNTEXT_HPP

#include <graphical_library/raylib/textbox/TextBox.hpp>
#include <iostream>

class DownText : public TextBox
{
public:
    DownText()
    : TextBox()
    {
        this->x = 950;
        this->y = 490;
        this->width = 300;
        this->height = 100;
        this->color = {200, 200, 200, 255};
        this->text = "Move Down";
        this->cColor = {0,0,0,255};
        this->alignment = LEFT;
    }
};

#endif /* DOWNTEXT_HPP */
