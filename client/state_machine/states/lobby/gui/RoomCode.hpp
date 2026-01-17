/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** loggin button
*/

#ifndef ROOM_CODE_HPP
#define ROOM_CODE_HPP

#include <graphical_library/raylib/textbox/TextBox.hpp>
#include <iostream>

class RoomCode : public TextBox
{
public:
    RoomCode()
    : TextBox()
    {
        this->width = 200;
        this->height = 60;
        this->x = 700;
        this->y = 50;
        this->color = {255, 255, 255, 255};
        this->text = "[CODE]";
    }

    auto onClick() -> void
    {
        std::cerr << this->text << std::endl;
    }
};

#endif /* ROOM_CODE_HPP */
