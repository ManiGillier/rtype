/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** test lobby button
*/

#ifndef TEST_LOBBY_BUTTON_HPP
#define TEST_LOBBY_BUTTON_HPP

#include <graphical_library/raylib/buttons/Button.hpp>
#include <iostream>

class TestLobbyButton : public Button
{
public:
    TestLobbyButton()
    : Button()
    {
        this->x = 20;
        this->y = 20;
        this->width = 100;
        this->height = 30;
        this->idleColor = { 100, 100, 100, 255 };
        this->hoverColor = { 70, 70, 70, 255 };
        this->pressedColor = { 150, 150, 150, 255 };
        this->text = "PRESS ME";
    }

    auto onClick() -> void
    {
        std::cerr << "Just clicked the button !" << std::endl;
    }
};

#endif /* TEST_LOBBY_BUTTON_HPP */
