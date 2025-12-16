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
#include "client/manager/SoundManager.hpp"
#include "client/manager/NetworkManager.hpp"
#include "logic.hpp"

class InGameStateGui : public GUI {
public:
    InGameStateGui(IGameState &, NetworkManager &, InGameStateLogic &);

    auto render(Registry &) -> void;
private:
    NetworkManager &networkManager;
    IGameState &gameState;
    InGameStateLogic &logic;
    TextureManager textureManager;
    SoundManager soundManager;
    Entity background;
};

#endif /* IN_GAME_STATE_GUI_HPP */
