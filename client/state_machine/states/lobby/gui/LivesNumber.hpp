/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** loggin button
*/

#ifndef LIVES_NUMBER_HPP
#define LIVES_NUMBER_HPP

#include <cstdint>
#include <graphical_library/raylib/textbox/TextBox.hpp>
#include <iostream>
#include <string>

#include "../Lobby.hpp"

class LivesNumber : public TextBox
{
public:
    LivesNumber(Lobby &lobby)
    : TextBox(), lobby(lobby)
    {
        this->width = 40;
        this->height = 40;
        this->x = 310;
        this->y = 560;
        this->color = {255, 255, 255, 255};
        this->text = "12";
    }

    inline auto update() -> void override {
        int const lives = this->lobby.getConfig().lives;

        this->text = std::to_string(lives);
    }
private:
    Lobby &lobby;
};

#endif /* LIVES_NUMBER_HPP */
