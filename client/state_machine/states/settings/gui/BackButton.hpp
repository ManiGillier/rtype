/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** client_settings_back_button
*/

#ifndef SETTINGS_GUI_BACK_BUTTON_HPP
#define SETTINGS_GUI_BACK_BUTTON_HPP

#include <graphical_library/raylib/buttons/Button.hpp>

#include "../Settings.hpp"

class BackButton : public Button
{
public:
    BackButton(Settings &state)
    : Button(), state(state)
    {
        this->x = 20;
        this->y = 20;
        this->width = 100;
        this->height = 50;
        this->idleColor = {200, 200, 200, 255};
        this->hoverColor = {225, 225, 225, 255};
        this->pressedColor = {250, 250, 250, 255};
        this->textColor = {0, 0, 0, 255};

        this->text = "BACK";
    }

    auto onClick() -> void
    {
        this->state.toMenu();
    }
private:
    Settings &state;
};

#endif /* SETTINGS_GUI_BACK_BUTTON_HPP */
