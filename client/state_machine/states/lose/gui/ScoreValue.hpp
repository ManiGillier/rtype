/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** Score value button
*/

#ifndef SCORE_VALUE_HPP
#define SCORE_VALUE_HPP

#include <graphical_library/raylib/textbox/TextBox.hpp>

class ScoreValue : public TextBox
{
public:
    ScoreValue()
    : TextBox()
    {
        this->x = 650;
        this->y = 220;
        this->width = 300;
        this->height = 70;
        this->color = {255, 100, 100, 255};
        this->cColor = {255, 255, 255, 255};
        this->text = "0";
    }
};

#endif /* SCORE_VALUE_HPP */
