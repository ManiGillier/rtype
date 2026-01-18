/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** lobby gui chat
*/

#ifndef LOBBY_GUI_CHAT_HPP
#define LOBBY_GUI_CHAT_HPP

#include <graphical_library/raylib/box/Box.hpp>
#include <graphical_library/raylib/textbox/TextBox.hpp>
#include <graphical_library/raylib/buttons/Button.hpp>
#include <graphical_library/raylib/inputbox/InputBox.hpp>
#include <string>

#include "../Lobby.hpp"

class ChatBox : public Box
{
public:
    ChatBox() : Box()
    {
        this->x = 0;
        this->y = 300;
        this->width = 400;
        this->height = 400;
        this->color = { 100, 100, 100, 50 };
    }
};

class ChatText : public TextBox
{
public:
    ChatText() : TextBox()
    {
        this->x = 0;
        this->y = 300;
        this->width = 400;
        this->height = 50;
        this->color = { 150, 150, 150, 50 };
        this->cColor = gl::BLACK;
        this->textColor = gl::WHITE;

        this->text = "Chat";
        this->alignment = LEFT;
    }
};

class ChatInput : public InputBox
{
public:
    ChatInput(Lobby &lobby) : InputBox(), lobby(lobby)
    {
        this->x = 0;
        this->y = 700;
        this->width = 350;
        this->height = 50;

        this->idleColor = { 80, 80, 80, 255 };
        this->selectedColor = { 120, 120, 120, 255 };

        this->textColor = gl::WHITE;

        this->text = "";
    }

    inline auto update() -> void
    {
        this->text = this->lobby.getMessage();
        InputBox::update();
    }

    auto onTextChange() -> void
    {
        this->lobby.setMessage(this->text);
    }
private:
    Lobby &lobby;
};

class ChatSend : public Button
{
public:
    ChatSend(Lobby &lobby) : Button(), lobby(lobby)
    {
        this->x = 350;
        this->y = 700;
        this->width = 50;
        this->height = 50;

        this->idleColor = { 80, 80, 80, 255 };
        this->hoverColor = { 120, 120, 120, 255 };
        this->pressedColor = { 140, 140, 140, 255 };

        this->textColor = gl::WHITE;

        this->text = ">";
    }

    auto onClick() -> void
    {
        this->lobby.sendNewMessage();
    }
private:
    Lobby &lobby;
};

class ChatEntry : public TextBox
{
public:
    ChatEntry(Lobby &lobby, int id) : TextBox(), lobby(lobby), id(id)
    {
        this->x = 10;
        this->height = 35;
        this->y = 700 - this->height * (this->id + 1);
        this->width = 380;
        this->color = { 0, 0, 0, 0 };
        this->cColor = { 0, 0, 0, 0 };
        this->lineThickness = 0;
        this->textColor = gl::WHITE;

        this->text = "Chat";
        this->alignment = LEFT;
    }

    inline auto update() -> void override
    {
        this->text = this->lobby.getChatMessage(this->id);
    }
private:
    Lobby &lobby;
    int id;
};

#endif /* LOBBY_GUI_CHAT_HPP */
