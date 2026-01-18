/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** menu gui play
*/

#ifndef MENU_GUI_PLAY_HPP
#define MENU_GUI_PLAY_HPP

#include <graphical_library/raylib/textbox/TextBox.hpp>
#include <graphical_library/raylib/box/Box.hpp>
#include <graphical_library/raylib/buttons/Button.hpp>
#include <graphical_library/raylib/inputbox/InputBox.hpp>

class PlayBox : public Box
{
public:
    PlayBox() : Box()
    {
        this->x = 100;
        this->y = 300;
        this->width = 400;
        this->height = 320;
        this->color = { 100, 100, 100, 255 };
    }
};

class PlayText : public TextBox
{
public:
    PlayText() : TextBox()
    {
        this->x = 100;
        this->y = 300;
        this->width = 400;
        this->height = 50;
        this->color = { 150, 150, 150, 255 };
        this->cColor = gl::BLACK;
        this->textColor = gl::WHITE;

        this->text = "Play options";
    }
};

class JoinRandomLobby : public Button
{
public:
    JoinRandomLobby() : Button()
    {
        this->x = 140;
        this->y = 380;
        this->width = 320;
        this->height = 50;

        this->idleColor = { 80, 80, 80, 255 };
        this->hoverColor = { 120, 120, 120, 255 };
        this->pressedColor = { 140, 140, 140, 255 };

        this->textColor = gl::WHITE;

        this->text = "Join public lobby";
    }
};

class CreatePrivateLobby : public Button
{
public:
    CreatePrivateLobby() : Button()
    {
        this->x = 140;
        this->y = 460;
        this->width = 320;
        this->height = 50;

        this->idleColor = { 80, 80, 80, 255 };
        this->hoverColor = { 120, 120, 120, 255 };
        this->pressedColor = { 140, 140, 140, 255 };

        this->textColor = gl::WHITE;

        this->text = "Create private lobby";
    }
};

class LobbyCode : public InputBox
{
public:
    LobbyCode() : InputBox()
    {
        this->x = 140;
        this->y = 540;
        this->width = 120;
        this->height = 50;

        this->idleColor = { 120, 120, 120, 255 };
        this->selectedColor = { 150, 150, 150, 255 };

        this->textColor = gl::WHITE;

        this->text = "";
    }
};

class JoinLobby : public Button
{
public:
    JoinLobby() : Button()
    {
        this->x = 140 + 150;
        this->y = 540;
        this->width = 320 - 150;
        this->height = 50;

        this->idleColor = { 80, 80, 80, 255 };
        this->hoverColor = { 120, 120, 120, 255 };
        this->pressedColor = { 140, 140, 140, 255 };

        this->textColor = gl::WHITE;

        this->text = "Join";
    }
};

#endif /* MENU_GUI_PLAY_HPP */
