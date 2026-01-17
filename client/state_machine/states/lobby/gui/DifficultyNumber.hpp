/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** loggin button
*/

#ifndef DIFFICULTY_NUMBER_HPP
#define DIFFICULTY_NUMBER_HPP

#include <graphical_library/raylib/textbox/TextBox.hpp>
#include <iostream>
#include <string>

#include "../Lobby.hpp"

class DifficultyNumber : public TextBox
{
public:
    DifficultyNumber(Lobby &lobby)
    : TextBox(), lobby(lobby)
    {
        this->width = 40;
        this->height = 40;
        this->x = 310;
        this->y = 360;
        this->color = {255, 255, 255, 255};
        this->text = "12";
    }

    inline auto update() -> void override {
        int const difficulty = this->lobby.getConfig().difficuly;

        this->text = std::to_string(difficulty);
    }
private:
    Lobby &lobby;
};

#endif /* DIFFICULTY_NUMBER_HPP */
