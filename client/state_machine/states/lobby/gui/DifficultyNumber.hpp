/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** loggin button
*/

#ifndef DIFFICULTY_NUMBER_HPP
#define DIFFICULTY_NUMBER_HPP

#include <graphical_library/raylib/textbox/TextBox.hpp>
#include <iostream>

class DifficultyNumber : public TextBox
{
public:
    DifficultyNumber()
    : TextBox()
    {
        this->width = 40;
        this->height = 40;
        this->x = 310;
        this->y = 200;
        this->color = {255, 255, 255, 255};
        this->text = "12";
    }

    auto onClick() -> void
    {
        std::cerr << this->text << std::endl;
    }
};

#endif /* DIFFICULTY_NUMBER_HPP */
