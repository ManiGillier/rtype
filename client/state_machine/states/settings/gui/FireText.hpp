/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** loggin button
*/

#ifndef FIRETEXT_HPP
#define FIRETEXT_HPP

#include <graphical_library/raylib/textbox/TextBox.hpp>
#include <iostream>

class FireText : public TextBox
{
public:
    FireText()
    : TextBox()
    {
        this->x = 950;
        this->y = 640;
        this->width = 300;
        this->height = 100;
        this->color = {200, 200, 200, 255};
        this->text = "Fire";
        this->cColor = {0,0,0,255};
        this->alignment = LEFT;
    }

    auto onClick() -> void
    {
        std::cerr << this->text << std::endl;
    }
};

#endif /* FIRETEXT_HPP */
