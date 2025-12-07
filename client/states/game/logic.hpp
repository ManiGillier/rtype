/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** in game state logic
*/

#ifndef IN_GAME_STATE_LOGIC_HPP
#define IN_GAME_STATE_LOGIC_HPP

#include "client/api/ILogic.hpp"
#include <optional>

class InGameStateLogic : public ILogic
{
public:
    InGameStateLogic(Registry &);

    auto update(Registry &) -> void;
private:
    std::optional<Entity> square;
};

#endif /* IN_GAME_STATE_LOGIC_HPP */
