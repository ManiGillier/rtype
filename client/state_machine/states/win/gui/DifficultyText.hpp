/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** test lobby button
*/

#ifndef DIFFICULTY_TEXT_HPP
#define DIFFICULTY_TEXT_HPP

#include <graphical_library/raylib/textbox/TextBox.hpp>

class DifficultyText : public TextBox
{
public:
    DifficultyText()
    : TextBox()
    {
        this->x = 600;
        this->y = 160;
        this->width = 400;
        this->height = 50;
        this->color = {100, 200, 255, 255};
        this->text = "Difficulty :";
        this->cColor = {255, 255, 255, 255};
    }
};

#endif /* DIFFICULTY_TEXT_HPP */
