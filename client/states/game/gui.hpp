/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** in game state gui
*/

#ifndef IN_GAME_STATE_GUI_HPP
#define IN_GAME_STATE_GUI_HPP

#include "client/api/GUI.hpp"
#include "client/api/IGameState.hpp"

#include "client/manager/TextureManager.hpp"

class InGameStateGui : public GUI {
public:
    InGameStateGui(IGameState &);

    auto render(Registry &) -> void;
private:
    IGameState &gameState;
    TextureManager textureManager;
    Entity background;
};

#endif /* IN_GAME_STATE_GUI_HPP */
