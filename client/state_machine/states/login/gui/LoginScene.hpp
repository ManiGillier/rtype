/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** login scene
*/

#ifndef LOGIN_SCENE_HPP
#define LOGIN_SCENE_HPP

#include "LoginButton.hpp"
#include "PasswordBox.hpp"
#include "UsernameBox.hpp"
#include <graphical_library/raylib/GuiScene.hpp>

class LoginScene : public GuiScene
{
public:
    LoginScene(gl::GraphicalLibrary &gl) : GuiScene(gl) {}

    auto init() -> void
    {
        this->add<LoginButton>();
        this->add<UsernameBox>();
        this->add<PasswordBox>();
    }
};

#endif /* LOGIN_SCENE_HPP */
