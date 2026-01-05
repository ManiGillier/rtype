/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** in game state gui
*/

#include "gui.hpp"

#include "logic.hpp"
#include "systems/Systems.hpp"

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
    Registry &r = gameState.getRegistry();

    this->textureManager.registerTexture("client/assets/background.jpg");

    r.add_render_system<HorizontalTiling, TextureComp>
        (animateTiling, std::ref(this->textureManager));
    r.add_render_system<HorizontalTiling, TextureComp>
        (renderHTiledTexture, std::ref(this->textureManager));

    r.add_render_system<Position, HitBox, ElementColor>
        (renderSquare, std::ref(this->gameState.getGraphicalLibrary()));
    r.add_render_system<Laser, Dependence, ElementColor>
        (renderLaser, std::ref(this->gameState.getGraphicalLibrary()));
    r.add_render_system<Position, PlayerId>(renderPlayerId,
                                            this->logic.getPlayerId());

    r.add_component<HorizontalTiling>(background, {2, 0, -50});
    r.add_component<TextureComp>(background, {"client/assets/background.jpg"});

    this->soundManager.loadSound("client/assets/new_player.mp3");
    this->soundManager.loadSound("client/assets/despawn_player.mp3");
    this->soundManager.loadSound("client/assets/laser.mp3");

    r.add_global_render_system(laserSound, std::ref(this->soundManager));

    nm.addExecutor(std::make_unique<NewPlayerSoundExecutor>
                       (std::ref(this->soundManager)));
    nm.addExecutor(std::make_unique<DespawnPlayerSoundExecutor>
                       (std::ref(this->soundManager)));
}

auto InGameStateGui::render(Registry &r) -> void
{
    this->textureManager.loadTextures();
    r.render();
}
