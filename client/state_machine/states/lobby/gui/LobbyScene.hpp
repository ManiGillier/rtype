/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** test lobby scene
*/

#ifndef TEST_LOBBY_SCENE_HPP
#define TEST_LOBBY_SCENE_HPP

#include "TestButton.hpp"
#include <graphical_library/raylib/GuiScene.hpp>

class LobbyScene : public GuiScene
{
public:
    LobbyScene(gl::GraphicalLibrary &gl) : GuiScene(gl) {}

    auto init() -> void
    {
        this->add<TestLobbyButton>();
    }
};

#endif /* TEST_LOBBY_SCENE_HPP */
