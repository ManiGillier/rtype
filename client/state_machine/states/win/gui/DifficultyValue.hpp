/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** test lobby button
*/

#ifndef DIFFICULTY_VALUE_HPP
#define DIFFICULTY_VALUE_HPP

#include <graphical_library/raylib/buttons/Button.hpp>
#include <graphical_library/raylib/textbox/TextBox.hpp>

class DifficultyValue : public TextBox
{
public:
    DifficultyValue()
    : TextBox()
    {
        this->x = 650;
        this->y = 220;
        this->width = 300;
        this->height = 70;
        this->color = {100, 200, 255, 255};
        this->text = "12";
        this->cColor = {0, 0, 0, 255};
    }
};


#endif /* DIFFICULTY_VALUE_HPP */
