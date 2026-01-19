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
    RoomCode(std::string code)
    : TextBox()
    {
        this->width = 150;
        this->height = 60;
        this->x = 740;
        this->y = 50;
        this->color = {255, 255, 255, 255};
        this->text = code;
    }
};

#endif /* ROOM_CODE_HPP */
