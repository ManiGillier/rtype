/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** in game state gui
*/

#include "gui.hpp"

#include "systems/Systems.hpp"

#include <raylib.h>

InGameStateGui::InGameStateGui(IGameState &gm) : gameState(gm),
    background(gm.getRegistry().spawn_entity())
{
    Registry &r = gameState.getRegistry();

    this->textureManager.registerTexture("client/assets/background.jpg");

    r.add_render_system<Position, HitBox, ElementColor>(renderSquare);
    r.add_render_system<Laser, Dependence, ElementColor>(renderLaser);
    r.add_render_system<HorizontalTiling, TextureComp>
        (animateTiling, std::ref(this->textureManager));
    r.add_render_system<HorizontalTiling, TextureComp>
        (renderHTiledTexture, std::ref(this->textureManager));

    r.add_component<HorizontalTiling>(background, {2, 0, -50});
    r.add_component<TextureComp>(background, {"client/assets/background.jpg"});
}

auto InGameStateGui::render(Registry &r) -> void
{
    this->textureManager.loadTextures();
    r.render();
}
