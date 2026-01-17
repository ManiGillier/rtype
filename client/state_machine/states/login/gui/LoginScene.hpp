/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** login scene
*/

#ifndef LOGIN_SCENE_HPP
#define LOGIN_SCENE_HPP

#include <graphical_library/raylib/GuiScene.hpp>

#include "../Login.hpp"

#include "LoginBox.hpp"
#include "RegisterBox.hpp"
#include "ErrorMessage.hpp"

class LoginScene : public GuiScene
{
public:
    LoginScene(gl::GraphicalLibrary &gl, Login &login)
    : GuiScene(gl), login(login) {}

    auto init() -> void
    {
        this->add<LoginBox>();
        this->add<LoginText>();
        this->add<LoginButton>(login);
        this->add<LoginPassword>(login);
        this->add<LoginUsername>(login);

        this->add<RegisterBox>();
        this->add<RegisterText>();
        this->add<RegisterButton>(login);
        this->add<RegisterPassword>(login);
        this->add<RegisterUsername>(login);

        this->add<ErrorMessage>(login);
    }
private:
    Login &login;
};

#endif /* LOGIN_SCENE_HPP */
