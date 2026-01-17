/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** test lobby button
*/

#ifndef PLUS_DIFFICULTY_BUTTON_HPP
#define PLUS_DIFFICULTY_BUTTON_HPP

#include <graphical_library/raylib/buttons/Button.hpp>
#include <iostream>

#include "../Lobby.hpp"

class PlusDifficulty : public Button
{
public:
    PlusDifficulty(Lobby &lobby)
    : Button(), lobby(lobby)
    {
        this->x = 370;
        this->y = 360;
        this->width = 40;
        this->height = 40;
        this->idleColor = {100, 100, 100, 255};
        this->hoverColor = {150, 150, 150, 255};
        this->pressedColor = {70, 70, 70, 255};
        this->text = "+";
    }

    auto onClick() -> void
    {
        GameStartConfig config = this->lobby.getConfig();

        if (config.difficuly < 15)
            config.difficuly++;
        this->lobby.setConfig(config);
    }
private:
    Lobby &lobby;
};

#endif /* PLUS_DIFFICULTY_BUTTON_HPP */
