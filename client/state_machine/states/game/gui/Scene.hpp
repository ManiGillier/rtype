/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** game scene
*/

#ifndef GAME_GUI_SCENE_HPP
#define GAME_GUI_SCENE_HPP

#include <graphical_library/raylib/GuiScene.hpp>

#include "Chat.hpp"

#include "../Game.hpp"

class GameScene : public GuiScene
{
public:
    GameScene(gl::GraphicalLibrary &gl, Game &game)
    : GuiScene(gl), game(game) {}

    auto init() -> void
    {
        this->add<game::ChatBox>();
        this->add<game::ChatText>();
        this->add<game::ChatInput>(game);
        this->add<game::ChatSend>(game);
        for (int i = 0; i < 10; i++)
            this->add<game::ChatEntry>(game, i);
     }
private:
    Game &game;
};

#endif /* GAME_GUI_SCENE_HPP */
