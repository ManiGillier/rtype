/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** loggin button
*/

#ifndef LIVES_NUMBER_HPP
#define LIVES_NUMBER_HPP

#include <graphical_library/raylib/textbox/TextBox.hpp>
#include <iostream>

class LivesNumber : public TextBox
{
public:
    LivesNumber()
    : TextBox()
    {
        this->width = 40;
        this->height = 40;
        this->x = 310;
        this->y = 280;
        this->color = {255, 255, 255, 255};
        this->text = "12";
    }

    auto onClick() -> void
    {
        std::cerr << this->text << std::endl;
    }
};

#endif /* LIVES_NUMBER_HPP */
