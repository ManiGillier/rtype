/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** username button
*/

#ifndef USERNAME_BOX_HPP
#define USERNAME_BOX_HPP

#include <graphical_library/raylib/inputbox/InputBox.hpp>

class UsernameBox : public InputBox
{
public:
UsernameBox():
    InputBox()
    {
        this->width = 500;
        this->height = 50;
        this->x = (1600 - this->width) / 2;
        this->y = 900 - this->height - 600;
        this->idleColor = { 200, 200, 200, 255 };
        this->selectedColor = {250, 250, 250, 255};
        this->textColor = gl::BLACK;
        this->text = "";
    }

    auto getText() -> std::string
    {
        return this->text;
    }
};

#endif /* USERNAME_BOX_HPP */
