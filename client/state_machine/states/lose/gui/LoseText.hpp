/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** test lobby button
*/

#ifndef LOSE_TEXT_HPP
#define LOSE_TEXT_HPP

#include <graphical_library/raylib/textbox/TextBox.hpp>

class LoseText : public TextBox
{
public:
    LoseText()
    : TextBox()
    {
        this->x = 500;
        this->y = 50;
        this->width = 600;
        this->height = 80;
        this->color = {120, 120, 200, 255};
        this->cColor = {180, 180, 255, 255};
        this->text = "YOU LOST";
    }
};

#endif /* LOSE_TEXT_HPP */

// this->pressedColor = {80, 80, 160, 255};
