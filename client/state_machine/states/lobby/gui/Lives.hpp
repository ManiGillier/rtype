/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** loggin button
*/

#ifndef LIVES_HPP
#define LIVES_HPP

#include <graphical_library/raylib/textbox/TextBox.hpp>
#include <iostream>

class Lives : public TextBox
{
public:
    Lives()
    : TextBox()
    {
        this->width = 120;
        this->height = 40;
        this->x = 250;
        this->y = 300;
        this->color = {255, 255, 255, 0};
        this->text = "Lives 🧡";
        this->cColor = {0,0,0,0};
    }

    auto onClick() -> void
    {
        std::cerr << this->text << std::endl;
    }
};

#endif /* LIVES_HPP */
