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
        this->width = 120;
        this->height = 40;
        this->x = 100;
        this->y = 200;
        this->color = {255, 255, 255, 255};
        this->text = "Difficulty :";
    }

    auto onClick() -> void
    {
        std::cerr << this->text << std::endl;
    }
};

#endif /* DIFFICULTY_HPP */
