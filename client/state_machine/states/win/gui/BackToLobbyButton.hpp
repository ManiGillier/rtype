/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** test lobby button
*/

#ifndef BACKTOLOBBY_BUTTON_HPP
#define BACKTOLOBBY_BUTTON_HPP

#include "client/state_machine/states/win/Win.hpp"
#include <graphical_library/raylib/buttons/Button.hpp>

class BackToLobbyButton : public Button
{
public:
    BackToLobbyButton(Win &win)
    : Button(), win(win)
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
        win.toMenu();
    }
private:
Win &win;
};

#endif /* BACKTOLOBBY_BUTTON_HPP */

// this->idleColor = {120, 120, 200, 255};
// this->hoverColor = {180, 180, 255, 255};
// this->pressedColor = {80, 80, 160, 255};
