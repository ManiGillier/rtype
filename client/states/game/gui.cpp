/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** in game state gui
*/

#include "gui.hpp"

#include "systems/Systems.hpp"

#include <raylib.h>

InGameStateGui::InGameStateGui(IGameState &gm) : gameState(gm)
{
    Registry &r = gameState.getRegistry();

    (void) r;
    //r.add_render_system<Position, Square>(renderSquare);
}

auto InGameStateGui::render(Registry &r) -> void
{
    r.render();
}

auto InGameStateGui::manageEvent(EventId id) -> EventState
{
    switch (id) {
        case EventId::LEFT:
            return EventState(IsKeyDown(KEY_LEFT));
        case EventId::RIGHT:
            return EventState(IsKeyDown(KEY_RIGHT));
        case EventId::UP:
            return EventState(IsKeyDown(KEY_UP));
        case EventId::DOWN:
            return EventState(IsKeyDown(KEY_DOWN));
        case EventId::SHOOT:
            return EventState(IsKeyDown(KEY_SPACE)
                              || IsMouseButtonDown(MOUSE_BUTTON_LEFT));
        default:
            return EventState();
    }
}

auto InGameStateGui::manageEvents(EventManager &eventManager) -> void
{
    eventManager.lockAccess();
    for (auto &&[id, event] : eventManager.getEvents())
        eventManager.setEventState(id, this->manageEvent(id));
    eventManager.unlockAccess();
}
