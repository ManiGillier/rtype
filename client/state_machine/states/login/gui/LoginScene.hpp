/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** login scene
*/

#ifndef LOGIN_SCENE_HPP
#define LOGIN_SCENE_HPP

#include <graphical_library/raylib/GuiScene.hpp>

#include "LoginBox.hpp"
#include "RegisterBox.hpp"

class LoginScene : public GuiScene
{
public:
    LoginScene(gl::GraphicalLibrary &gl) : GuiScene(gl) {}

    auto init() -> void
    {
        this->add<LoginBox>();
        this->add<LoginText>();
        this->add<LoginButton>();
        this->add<LoginPassword>();
        this->add<LoginUsername>();

        this->add<RegisterBox>();
        this->add<RegisterText>();
        this->add<RegisterButton>();
        this->add<RegisterPassword>();
        this->add<RegisterUsername>();
    }
};

#endif /* LOGIN_SCENE_HPP */
