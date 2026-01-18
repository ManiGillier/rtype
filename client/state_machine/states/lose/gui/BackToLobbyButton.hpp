/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** test lobby button
*/

#ifndef BACKTOLOBBY_BUTTON_HPP
#define BACKTOLOBBY_BUTTON_HPP

#include <graphical_library/raylib/buttons/Button.hpp>
#include <iostream>

class BackToLobbyButton : public Button
{
public:
    BackToLobbyButton()
    : Button()
    {
        this->x = 650;
        this->y = 700;
        this->width = 300;
        this->height = 55;
        this->idleColor = {120, 200, 120, 255};
        this->hoverColor = {180, 255, 180, 255};
        this->pressedColor = {80, 160, 80, 255};
        this->text = "BACK TO MENU";
    }
    auto onClick() -> void
    {
        std::cout << "Je suis cliqué :o" << std::endl;
    }
};

#endif /* BACKTOLOBBY_BUTTON_HPP */
