/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** menu gui text
*/

#ifndef MENU_GUI_TEXT_HPP
#define MENU_GUI_TEXT_HPP

#include <graphical_library/raylib/textbox/TextBox.hpp>

class MenuText : public TextBox
{
public:
    MenuText() : TextBox()
    {
        this->x = 0;
        this->y = 0;
        this->width = 1600;
        this->height = 200;
        this->lineThickness = 0;
        this->color = { 0, 0, 0, 0 };
        this->cColor = { 0, 0, 0, 0 };
        this->textColor = gl::WHITE;
        this->text = "R-TYPE";
    }
};

#endif /* MENU_GUI_TEXT_HPP */
