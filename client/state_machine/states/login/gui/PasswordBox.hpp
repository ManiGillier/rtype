/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** password button
*/

#ifndef PASSWORD_BOX_HPP
#define PASSWORD_BOX_HPP

#include <graphical_library/raylib/inputbox/InputBox.hpp>
#include <iostream>

class PasswordBox : public InputBox
{
public:
PasswordBox():
    InputBox()
    {
        this->width = 500;
        this->height = 50;
        this->x = (1600 - this->width) / 2;
        this->y = 900 - this->height - 500;
        this->idleColor = { 200, 200, 200, 255 };
        this->selectedColor = {250, 250, 250, 255};
        this->textColor = gl::BLACK;
        this->text = "";
    }

    auto onTextChange() -> void
    {
        std::cout << this->getText() << std::endl;
    }
};

#endif /* PASSWORD_BOX_HPP */
