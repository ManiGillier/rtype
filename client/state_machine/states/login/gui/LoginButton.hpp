/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** loggin button
*/

#ifndef LOGIN_BUTTON_HPP
#define LOGIN_BUTTON_HPP

#include <graphical_library/raylib/buttons/Button.hpp>
#include <iostream>

class LoginButton : public Button
{
public:
    LoginButton()
    : Button()
    {
        this->width = 250;
        this->height = 60;
        this->x = (1600 - this->width) / 2;
        this->y = 900 - this->height - 400;
        this->idleColor = { 100, 100, 100, 255 };
        this->hoverColor = { 70, 70, 70, 255 };
        this->pressedColor = { 150, 150, 150, 255 };
        this->text = "LOGIN";
    }

    auto onClick() -> void
    {
        std::cerr << this->text << std::endl;
    }
};

#endif /* LOGIN_BUTTON_HPP */
