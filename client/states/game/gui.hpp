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

class InGameStateGui : public GUI {
public:
    InGameStateGui(IGameState &);

    auto render(Registry &) -> void;
    auto manageEvents(EventManager &) -> void;
protected:
    auto manageEvent(EventId) -> EventState;
private:
    IGameState &gameState;
};

#endif /* IN_GAME_STATE_GUI_HPP */
