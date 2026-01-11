/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** game state
*/

#include "Game.hpp"

#include "shared/components/Position.hpp"
#include "shared/components/Dependence.hpp"
#include "shared/components/Health.hpp"
#include "shared/components/HitBox.hpp"
#include "shared/components/Laser.hpp"

#include "client/components/Color.hpp"
#include "client/components/HorizontalTiling.hpp"
#include "client/components/PlayerId.hpp"
#include "client/components/Texture.hpp"

#include "client/network/executor/NewPlayerExecutor.hpp"
#include "client/network/executor/NewEnemyExecutor.hpp"
#include "client/network/executor/NewBulletExecutor.hpp"
#include "client/network/executor/DespawnPlayerExecutor.hpp"
#include "client/network/executor/DespawnBulletExecutor.hpp"
#include "client/network/executor/EnemyDiedExecutor.hpp"
#include "client/network/executor/PlayerIdExecutor.hpp"
#include "client/network/executor/GameOverExecutor.hpp"
#include "client/network/executor/HealthUpdateExecutor.hpp"
#include "client/network/executor/HitboxSizeUpdateExecutor.hpp"
#include "client/network/executor/LaserActivateUpdateExecutor.hpp"
#include "client/network/executor/PositionUpdateExecutor.hpp"

#include "network/packets/impl/ClientInputsPacket.hpp"

#include "systems/Systems.hpp"

Game::Game(ClientManager &cm, Registry &r, Sync &s)
    : State(cm, r, s)
{}

auto Game::init_systems() -> void
{
    NetworkManager &nm = this->clientManager.getNetworkManager();

    this->registry.reset_update_systems();
    this->registry.reset_render_systems();

    nm.resetExecutors();

    this->registry.register_component<Position>();
    this->registry.register_component<Dependence>();
    this->registry.register_component<Health>();
    this->registry.register_component<HitBox>();
    this->registry.register_component<Laser>();
    this->registry.register_component<ElementColor>();
    this->registry.register_component<HorizontalTiling>();
    this->registry.register_component<PlayerId>();
    this->registry.register_component<TextureComp>();

    this->registry.add_render_system<HorizontalTiling, TextureComp>
        (animateTiling, std::ref(this->clientManager.getGui()));
    this->registry.add_render_system<HorizontalTiling, TextureComp>
        (renderHTiledTexture, std::ref(this->clientManager.getGui()));

    Entity background = this->registry.spawn_named_entity("background");
    this->registry.add_component<HorizontalTiling>(background, {2, 0, -50});
    this->registry.add_component<TextureComp>
        (background, {"background"});


    this->registry.add_render_system<Position, HitBox, ElementColor>
        (renderSquare, std::ref(this->getGraphicalLibrary()));
    this->registry.add_render_system<Laser, Dependence, ElementColor>
        (renderLaser, std::ref(this->getGraphicalLibrary()));
    this->registry.add_render_system<Position, PlayerId>
        (renderPlayerId, std::ref(this->getGraphicalLibrary()),
         std::ref(this->clientId));

    this->registry.add_global_update_system
        (playerInputs, std::ref(this->clientManager.getGui()),
         std::ref(this->clientManager.getNetworkManager()));

    nm.addExecutor(std::make_unique<NewPlayerExecutor>(*this));
    nm.addExecutor(std::make_unique<NewEnemyExecutor>(*this));
    nm.addExecutor(std::make_unique<NewBulletExecutor>(*this));
    nm.addExecutor(std::make_unique<DespawnPlayerExecutor>(*this));
    nm.addExecutor(std::make_unique<DespawnBulletExecutor>(*this));
    nm.addExecutor(std::make_unique<EnemyDiedExecutor>(*this));
    nm.addExecutor(std::make_unique<PlayerIdExecutor>(*this));
    nm.addExecutor(std::make_unique<GameOverExecutor>(*this));
    nm.addExecutor(std::make_unique<HealthUpdateExecutor>(*this));
    nm.addExecutor(std::make_unique<HitboxSizeUpdateExecutor>(*this));
    nm.addExecutor(std::make_unique<LaserActiveUpdateExecutor>(*this));
    nm.addExecutor(std::make_unique<PositionUpdateExecutor>(*this));
}

auto Game::init_entities() -> void {}

auto Game::newPlayer(std::size_t player_id, std::size_t laser_id)
-> void
{
    Registry &r = this->registry;
    Entity player = r.spawn_entity();
    Entity laser = r.spawn_entity();

    this->sync.add(player.getId(), player_id);
    this->sync.add(laser.getId(), laser_id);
    r.add_component<Position>(player, {-200, -500});
    r.add_component<HitBox>(player, {20, 20});
    r.add_component<ElementColor>(player, {gl::WHITE});
    r.add_component<Health>(player, {0, 0});
    r.add_component<PlayerId>(player, {this->playerId});
    this->playerId++;

    r.add_component<Dependence>(laser, {player.getId()});
    r.add_component<Laser>(laser, {true, 30});
    r.add_component<ElementColor>(laser, {gl::GREEN});
}

auto Game::newEnemy(std::size_t enemy_id) -> void
{
    Registry &r = this->registry;
    Entity enemy = r.spawn_entity();

    this->sync.add(enemy.getId(), enemy_id);
    r.add_component<Position>(enemy, {-200, -200});
    r.add_component<HitBox>(enemy, {50, 50});
    r.add_component<ElementColor>(enemy, {gl::MAGENTA});
    r.add_component<Health>(enemy, {0, 0});
}

auto Game::newBullet(std::size_t bullet_id) -> void
{
    Registry &r = this->registry;
    Entity bullet = r.spawn_entity();

    this->sync.add(bullet.getId(), bullet_id);
    r.add_component<Position>(bullet, {-250, -200});
    r.add_component<HitBox>(bullet, {10, 10});
    r.add_component<ElementColor>(bullet, {gl::BLUE});
}

auto Game::despawnEntity(std::size_t id) -> void
{
    Registry &r = this->registry;
    std::optional<std::size_t> my_id = this->sync.get_mine_from_theirs(id);
    this->sync.del_with_theirs(id);

    if (!my_id)
        return;
    r.kill_entity(r.entity_from_index(*my_id));
}

auto Game::registerClientId(std::size_t id) -> void
{
    this->clientId = this->sync.get_mine_from_theirs(id);

    if (!this->clientId)
        return;
}

/*auto Game::end() -> void
{
    this->shouldStop = true;
}
*/

auto Game::updateHealth(std::size_t id, float health,
                                    float max_health) -> void
{
    std::optional<std::size_t> my_id = this->sync.get_mine_from_theirs(id);

    if (!my_id)
        return;
    this->registry.set<Health>(*my_id, (int) health,
                                              (int) max_health);
}

auto Game::updateHitbox(std::size_t id, float width, float height)
-> void
{
    std::optional<std::size_t> my_id = this->sync.get_mine_from_theirs(id);

    if (!my_id)
        return;
    this->registry.set<HitBox>(*my_id, width, height);
}

auto Game::updateLaser(std::size_t id, bool active, float length)
-> void
{
    std::optional<std::size_t> my_id = this->sync.get_mine_from_theirs(id);

    if (!my_id)
        return;
    this->registry.set<Laser>(*my_id, active, length);
}

auto Game::updatePosition(std::size_t id, float x, float y)
-> void
{
    std::optional<std::size_t> my_id = this->sync.get_mine_from_theirs(id);

    if (!my_id) {
        return;
    }
    this->registry.set<Position>(*my_id, x, y);
}
