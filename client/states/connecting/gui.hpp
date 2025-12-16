/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** connecting state gui
*/

#ifndef CONNECTING_STATE_GUI_HPP
#define CONNECTING_STATE_GUI_HPP

#include "client/api/GUI.hpp"
#include "client/api/IGameState.hpp"

class ConnectingStateGui : public GUI
{
public:
    ConnectingStateGui(IGameState &);

    auto render(Registry &) -> void;
private:
    IGameState &gameState;
};

#endif /* CONNECTING_STATE_GUI_HPP */
