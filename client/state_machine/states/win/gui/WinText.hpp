/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** test lobby button
*/

#ifndef WIN_TEXT_HPP
#define WIN_TEXT_HPP

#include <graphical_library/raylib/textbox/TextBox.hpp>

class WinText : public TextBox
{
public:
    WinText()
    : TextBox()
    {
        this->x = 500;
        this->y = 50;
        this->width = 600;
        this->height = 80;
        this->color = {255, 215, 0, 255};
        this->text = "YOU WON";
        this->cColor = {0, 0, 0, 255};
    }
};

#endif /* WIN_TEXT_HPP */
