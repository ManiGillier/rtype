/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** in game state gui
*/

#ifndef IN_GAME_STATE_GUI_HPP
#define IN_GAME_STATE_GUI_HPP

#include "client/api/GUI.hpp"

class InGameStateGui : public GUI {
public:
    InGameStateGui(Registry &);

    auto render(Registry &) -> void;
};

#endif /* IN_GAME_STATE_GUI_HPP */
