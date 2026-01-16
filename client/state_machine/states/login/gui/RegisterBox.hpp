/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** register box
*/

#ifndef REGISTER_BOX_HPP
#define REGISTER_BOX_HPP

#include <graphical_library/raylib/box/Box.hpp>
#include <graphical_library/raylib/textbox/TextBox.hpp>
#include <graphical_library/raylib/buttons/Button.hpp>
#include <graphical_library/raylib/inputbox/InputBox.hpp>

namespace R {
[[maybe_unused]] int const START_X = 825;
[[maybe_unused]] int const START_Y = 350;

[[maybe_unused]] int const SPACE_X = 50;
[[maybe_unused]] int const SPACE_Y = 50;

[[maybe_unused]] int const TOTAL_WIDTH = 800;
[[maybe_unused]] int const TOTAL_HEIGHT = 500;
}

class RegisterBox : public Box
{
public:
    RegisterBox() : Box() {
        this->x = R::START_X;
        this->y = R::START_Y;
        this->width = R::TOTAL_WIDTH - (int) (1.5 * R::SPACE_X);
        this->height = R::TOTAL_HEIGHT - (2 * R::SPACE_Y);
        this->color = { 90, 90, 90, 255 };
    }
};

class RegisterText : public TextBox
{
public:
    RegisterText() : TextBox() {
        this->width = R::TOTAL_WIDTH - (int) (R::SPACE_X * 1.5);
        this->height = R::SPACE_Y;
        this->x = R::START_X;
        this->y = R::START_Y - this->height;
        this->color = { 120, 120, 120, 255 };

        this->textColor = gl::BLACK;

        this->text = "REGISTER to create a new account";
    }
};

class RegisterUsername : public InputBox
{
public:
RegisterUsername():
    InputBox()
    {
        using namespace R;
        this->width = TOTAL_WIDTH - (int) (3.5 * SPACE_X);
        this->height = SPACE_Y;
        this->x = START_X + (TOTAL_WIDTH - this->width) / 2
                  - (int) (0.75 * SPACE_X);
        this->y = START_Y + TOTAL_HEIGHT - this->height - 8 * SPACE_Y;
        this->idleColor = { 200, 200, 200, 255 };
        this->selectedColor = {250, 250, 250, 255};
        this->textColor = gl::BLACK;
        this->text = "";
    }

    auto onTextChange() -> void
    {}
};

class RegisterPassword : public InputBox
{
public:
RegisterPassword():
    InputBox()
    {
        using namespace R;
        this->width = TOTAL_WIDTH - (int) (3.5 * SPACE_X);
        this->height = SPACE_Y;
        this->x = START_X + (TOTAL_WIDTH - this->width) / 2
                  - (int) (0.75 * SPACE_X);
        this->y = START_Y + TOTAL_HEIGHT - this->height - 6 * SPACE_Y;
        this->idleColor = { 200, 200, 200, 255 };
        this->selectedColor = {250, 250, 250, 255};
        this->textColor = gl::BLACK;
        this->text = "";
    }

    auto onTextChange() -> void
    {}
};

class RegisterButton : public Button
{
public:
    RegisterButton() : Button()
    {
        using namespace R;
        this->width = TOTAL_WIDTH - (int) (3.5 * SPACE_X);
        this->height = SPACE_Y * 2;
        this->x = START_X + (TOTAL_WIDTH - this->width) / 2
                  - (int) (0.75 * SPACE_X);
        this->y = START_Y + TOTAL_HEIGHT - this->height - 3 * SPACE_Y;
        this->idleColor = { 70, 70, 70, 255 };
        this->hoverColor = { 100, 100, 100, 255 };
        this->pressedColor = { 150, 150, 150, 255 };
        this->textColor = gl::BLACK;
        this->text = "REGISTER";
    }

    auto onClick() -> void
    {}
};

#endif /* REGISTER_BOX_HPP */
