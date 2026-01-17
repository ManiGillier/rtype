/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** loggin button
*/

#ifndef RIGHTTEXT_HPP
#define RIGHTTEXT_HPP

#include <graphical_library/raylib/textbox/TextBox.hpp>
#include <iostream>

class RightText : public TextBox
{
public:
    RightText()
    : TextBox()
    {
        this->y = 340;
        this->x = 950;
        this->width = 300;
        this->height = 100;
        this->color = {200, 200, 200, 255};
        this->text = "Move Right";
        this->cColor = {0,0,0,255};
        this->alignment = LEFT;
    }

    auto onClick() -> void
    {
        std::cerr << this->text << std::endl;
    }
};

#endif /* RIGHTTEXT_HPP */
