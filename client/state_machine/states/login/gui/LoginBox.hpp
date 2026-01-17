/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** login box
*/

#ifndef LOGIN_BOX_HPP
#define LOGIN_BOX_HPP

#include <graphical_library/raylib/box/Box.hpp>
#include <graphical_library/raylib/textbox/TextBox.hpp>
#include <graphical_library/raylib/buttons/Button.hpp>
#include <graphical_library/raylib/inputbox/InputBox.hpp>

#include "../Login.hpp"

namespace L {
[[maybe_unused]] int const START_X = 50;
[[maybe_unused]] int const START_Y = 350;

[[maybe_unused]] int const SPACE_X = 50;
[[maybe_unused]] int const SPACE_Y = 50;

[[maybe_unused]] int const TOTAL_WIDTH = 800;
[[maybe_unused]] int const TOTAL_HEIGHT = 500;
}

class LoginBox : public Box
{
public:
    LoginBox() : Box() {
        this->x = L::START_X;
        this->y = L::START_Y;
        this->width = L::TOTAL_WIDTH - (int) (1.5 * L::SPACE_X);
        this->height = L::TOTAL_HEIGHT - (2 * L::SPACE_Y);
        this->color = { 90, 90, 90, 255 };
    }
};

class LoginText : public TextBox
{
public:
    LoginText() : TextBox() {
        this->width = L::TOTAL_WIDTH - (int) (L::SPACE_X * 1.5);
        this->height = L::SPACE_Y;
        this->x = L::START_X;
        this->y = L::START_Y - this->height;
        this->color = { 120, 120, 120, 255 };

        this->textColor = gl::BLACK;

        this->text = "If you already have an account, please LOGIN";
    }
};

class LoginUsername : public InputBox
{
public:
LoginUsername(Login &login):
    InputBox(), login(login)
    {
        using namespace L;
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
    {
        this->login.setLoginUsername(this->text);
    }
private:
    Login &login;
};

class LoginPassword : public InputBox
{
public:
LoginPassword(Login &login):
    InputBox(), login(login)
    {
        using namespace L;
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
    {
        this->login.setLoginPassword(this->text);
    }
private:
    Login &login;
};

class LoginButton : public Button
{
public:
    LoginButton(Login &login) : Button(), login(login)
    {
        using namespace L;
        this->width = TOTAL_WIDTH - (int) (3.5 * SPACE_X);
        this->height = SPACE_Y * 2;
        this->x = START_X + (TOTAL_WIDTH - this->width) / 2
                  - (int) (0.75 * SPACE_X);
        this->y = START_Y + TOTAL_HEIGHT - this->height - 3 * SPACE_Y;
        this->idleColor = { 70, 70, 70, 255 };
        this->hoverColor = { 100, 100, 100, 255 };
        this->pressedColor = { 150, 150, 150, 255 };
        this->textColor = gl::BLACK;
        this->text = "LOGIN";
    }

    auto onClick() -> void
    {
        this->login.login();
    }
private:
    Login &login;
};

#endif /* LOGIN_BOX_HPP */
