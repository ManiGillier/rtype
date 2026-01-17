/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** test lobby button
*/

#ifndef MINUS_DIFFICULTY_BUTTON_HPP
#define MINUS_DIFFICULTY_BUTTON_HPP

#include <cstdint>
#include <graphical_library/raylib/buttons/Button.hpp>
#include <iostream>

#include "../Lobby.hpp"

class MinusDifficulty : public Button
{
public:
    MinusDifficulty(Lobby &lobby)
    : Button(), lobby(lobby)
    {
        this->x = 250;
        this->y = 360;
        this->width = 40;
        this->height = 40;
        this->idleColor = {100, 100, 100, 255};
        this->hoverColor = {150, 150, 150, 255};
        this->pressedColor = {70, 70, 70, 255};
        this->text = "-";
    }

    auto onClick() -> void
    {
        GameStartConfig config = this->lobby.getConfig();

        if (config.difficuly > 1)
            config.difficuly--;
        this->lobby.setConfig(config);
    }
private:
    Lobby &lobby;
};

#endif /* MINUS_DIFFICULTY_BUTTON_HPP */
