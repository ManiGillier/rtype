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
        this->x = 100;
        this->y = 280;
        this->color = {255, 255, 255, 255};
        this->text = "Lives :";
    }

    auto onClick() -> void
    {
        std::cerr << this->text << std::endl;
    }
};

#endif /* LIVES_HPP */
