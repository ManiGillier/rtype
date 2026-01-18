/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** menu gui scene
*/

#ifndef MENU_GUI_SCENE_HPP
#define MENU_GUI_SCENE_HPP

#include <graphical_library/raylib/GuiScene.hpp>

#include "../Menu.hpp"

#include "Text.hpp"
#include "Play.hpp"

class MenuScene : public GuiScene
{
public:
    MenuScene(gl::GraphicalLibrary &gl, Menu &menu)
    : GuiScene(gl), menu(menu) {}

    auto init() -> void
    {
        this->add<MenuText>();

        this->add<PlayBox>();
        this->add<PlayText>();
        this->add<JoinRandomLobby>(menu);
        this->add<CreatePrivateLobby>(menu);
        this->add<LobbyCode>(menu);
        this->add<JoinLobby>(menu);
    }
private:
    [[maybe_unused]] Menu &menu;
};

#endif /* MENU_GUI_SCENE_HPP */
