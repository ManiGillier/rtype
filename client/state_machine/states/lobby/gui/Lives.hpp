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
        this->x = 175;
        this->y = 300;

        this->width = 300;
        this->height = 40;
        this->y = 500;
        this->color = {0, 0, 0, 75};
        this->text = "Lives";
        this->cColor = {0,0,0,255};
    }

    auto onClick() -> void
    {
        std::cerr << this->text << std::endl;
    }
};

#endif /* LIVES_HPP */
