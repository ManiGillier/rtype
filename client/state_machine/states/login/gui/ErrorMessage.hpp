/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** error message
*/

#ifndef LOGIN_GUI_ERROR_MESSAGE_HPP
#define LOGIN_GUI_ERROR_MESSAGE_HPP

#include <graphical_library/raylib/textbox/TextBox.hpp>

#include "../Login.hpp"

class ErrorMessage : public TextBox
{
public:
    ErrorMessage(Login &login) : TextBox(), login(login)
    {
        this->width = 1500;
        this->height = 50;
        this->x = 50;
        this->y = 200;
        this->color = { 120, 100, 100, 255 };

        this->textColor = gl::RED;

        this->text = "ERROR: Reason";
    }

    inline auto update() -> void override
    {
        std::string error = this->login.getLastErrorMessage();
        this->color.a = error.empty() ? 0 : 255;
        this->text = error.empty() ? "" : "ERROR: " + error;
    }
private:
    Login &login;
};

#endif /* LOGIN_GUI_ERROR_MESSAGE_HPP */
