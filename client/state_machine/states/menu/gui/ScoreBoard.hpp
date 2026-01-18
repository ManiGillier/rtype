/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** menu gui scoreboard
*/

#ifndef MENU_GUI_SCOREBOARD_HPP
#define MENU_GUI_SCOREBOARD_HPP

#include <graphical_library/raylib/box/Box.hpp>
#include <graphical_library/raylib/textbox/TextBox.hpp>
#include <graphical_library/raylib/buttons/Button.hpp>
#include <string>

#include "../Menu.hpp"

class ScoreBox : public Box
{
public:
    ScoreBox() : Box()
    {
        this->x = 1100;
        this->y = 300;
        this->width = 400;
        this->height = 400;
        this->color = { 100, 100, 100, 255 };
    }
};

class ScoreboardText : public TextBox
{
public:
    ScoreboardText() : TextBox()
    {
        this->x = 1100;
        this->y = 300;
        this->width = 400;
        this->height = 50;
        this->color = { 150, 150, 150, 255 };
        this->cColor = gl::BLACK;
        this->textColor = gl::WHITE;

        this->text = "Scoreboard";
        this->alignment = LEFT;
    }
};

class ScoreboardRefresh : public Button
{
public:
    ScoreboardRefresh(Menu &menu) : Button(), menu(menu)
    {
        this->x = 1395;
        this->y = 305;
        this->width = 100;
        this->height = 40;

        this->idleColor = { 80, 80, 80, 255 };
        this->hoverColor = { 120, 120, 120, 255 };
        this->pressedColor = { 140, 140, 140, 255 };

        this->textColor = gl::WHITE;

        this->text = "Refresh";        
    }

    auto onClick() -> void
    {
        this->menu.requestScoresRefresh();
    }
private:
    Menu &menu;
};

class ScoreboardEntry : public TextBox
{
public:
    ScoreboardEntry(Menu &menu, int id) : TextBox(), menu(menu), id(id)
    {
        this->x = 1110;
        this->height = 33;
        this->y = 360 + this->height * this->id;
        this->width = 380;
        this->color = { 0, 0, 0, 0 };
        this->cColor = { 0, 0, 0, 0 };
        this->lineThickness = 0;
        this->textColor = gl::WHITE;

        this->text = "Scoreboard";
        this->alignment = LEFT;
    }

    inline auto update() -> void override
    {
        std::string score = this->menu.getScore(this->id);

        if (score.empty()) {
            this->text = "";
            return;
        }
        this->text = std::to_string(this->id) + ". " + score;
    }
private:
    Menu &menu;
    int id;
};

#endif /* MENU_GUI_SCOREBOARD_HPP */
