/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** test lobby button
*/

#ifndef CLIENT_SCORE_HPP
#define CLIENT_SCORE_HPP

#include <graphical_library/raylib/buttons/Button.hpp>
#include <graphical_library/raylib/textbox/TextBox.hpp>

class ScoreText : public TextBox
{
public:
    ScoreText()
    : TextBox()
    {
        this->x = 600;
        this->y = 160;
        this->width = 400;
        this->height = 50;
        this->color = {255, 100, 100, 255};
        this->cColor = {255, 255, 255, 255};
        this->text = "Your score :";
    }
};


#endif /* CLIENT_SCORE_HPP */
