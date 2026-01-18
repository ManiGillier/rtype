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
        this->add<ChatBox>();
        this->add<ChatText>();
        this->add<ChatInput>(game);
        this->add<ChatSend>(game);
        for (int i = 0; i < 10; i++)
            this->add<ChatEntry>(game, i);
     }
private:
    Game &game;
};

#endif /* GAME_GUI_SCENE_HPP */
