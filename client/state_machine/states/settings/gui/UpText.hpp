/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** loggin button
*/

#ifndef UPTEXT_HPP
#define UPTEXT_HPP

#include <graphical_library/raylib/textbox/TextBox.hpp>
#include <iostream>

class UpText : public TextBox
{
public:
    UpText()
    : TextBox()
    {
        this->x = 950;
        this->y = 40;
        this->width = 300;
        this->height = 100;
        this->color = {200, 200, 200, 255};
        this->text = "Move Up";
        this->cColor = {0,0,0,255};
        this->alignment = LEFT;
    }

    auto onClick() -> void
    {
        std::cerr << this->text << std::endl;
    }
};

#endif /* UPTEXT_HPP */
