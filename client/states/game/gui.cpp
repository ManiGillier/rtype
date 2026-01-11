/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** in game state gui
*/

#include "gui.hpp"

#include "logic.hpp"

#include <functional>
#include <memory>
#include <raylib.h>

#include "client/network/executor/NewPlayerSoundExecutor.hpp"
#include "client/network/executor/DespawnPlayerSoundExecutor.hpp"

InGameStateGui::InGameStateGui(IGameState &gm, NetworkManager &nm,
                               InGameStateLogic &logic)
    : networkManager(nm), gameState(gm), logic(logic),
      background(gm.getRegistry().spawn_entity())
{
}

auto InGameStateGui::render(Registry &r) -> void
{
    r.render();
}
