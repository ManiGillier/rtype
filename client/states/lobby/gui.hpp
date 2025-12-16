/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** lobby state gui
*/

#ifndef LOBBY_STATE_GUI_HPP
#define LOBBY_STATE_GUI_HPP

#include "client/api/GUI.hpp"
#include "client/api/IGameState.hpp"

class LobbyStateGui : public GUI
{
public:
    LobbyStateGui(IGameState &);

    auto render(Registry &) -> void;
private:
    IGameState &gameState;
};

#endif /* LOBBY_STATE_GUI_HPP */
