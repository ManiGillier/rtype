/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** test lobby button
*/

#ifndef HEADERGUARDS_HPP
#define HEADERGUARDS_HPP

#include <graphical_library/raylib/buttons/Button.hpp>
#include <graphical_library/raylib/textbox/TextBox.hpp>

class Nom : public Button
{
public:
    Nom()
    : Button()
    {
        this->x = 175;
        this->y = 300;
        this->width = 300;
        this->height = 120;
        this->idleColor = {150, 150, 150, 255};
        this->hoverColor = {150, 150, 150, 255};
        this->pressedColor = {150, 150, 150, 255};
        this->text = "";
    }
};

#endif /* HEADERGUARDS_HPP */
