/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** menu gui settings
*/

#ifndef MENU_GUI_SETTINGS_HPP
#define MENU_GUI_SETTINGS_HPP

#include <graphical_library/raylib/buttons/Button.hpp>

#include "../Menu.hpp"

class SettingsOpen : public Button
{
public:
    SettingsOpen(Menu &menu) : Button(), menu(menu)
    {
        this->width = 1000;
        this->x = 1600 / 2 - width / 2;
        this->y = 800;
        this->height = 60;

        this->idleColor = { 80, 80, 80, 255 };
        this->hoverColor = { 120, 120, 120, 255 };
        this->pressedColor = { 140, 140, 140, 255 };

        this->textColor = gl::WHITE;

        this->text = "SETTINGS";
    }

    auto onClick() -> void
    {
        this->menu.settings();
    }
private:
    Menu &menu;
};


#endif /* MENU_GUI_SETTINGS_HPP */
