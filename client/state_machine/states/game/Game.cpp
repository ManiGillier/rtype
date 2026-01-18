/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** game state
*/

#include "Game.hpp"

#include "gui/Scene.hpp"
#include "shared/components/Position.hpp"
#include "shared/components/Dependence.hpp"
#include "shared/components/Health.hpp"
#include "shared/components/HitBox.hpp"
#include "shared/components/Laser.hpp"

#include "client/components/Color.hpp"
#include "client/components/HorizontalTiling.hpp"
#include "client/components/PlayerId.hpp"
#include "client/components/Texture.hpp"
#include "client/components/StraightMoving.hpp"

#include "client/network/executor/NewEnemyExecutor.hpp"
#include "client/network/executor/NewBulletExecutor.hpp"
#include "client/network/executor/GameOverExecutor.hpp"
#include "client/network/executor/HitboxSizeUpdateExecutor.hpp"
#include "client/network/executor/LaserActivateUpdateExecutor.hpp"
#include "client/network/executor/PositionUpdateExecutor.hpp"
#include "client/network/executor/UpdateTimeExecutor.hpp"
#include "client/network/executor/LinkPlayersExecutor.hpp"
#include "client/network/executor/DestroyEntityExecutor.hpp"
#include "client/network/executor/PlayerHitExecutor.hpp"
#include "client/network/executor/TextChatStringExecutorGame.hpp"

#include "network/packets/impl/ClientInputsPacket.hpp"
#include "network/packets/impl/TextChatStringPacket.hpp"

#include "gui/Scene.hpp"

#include "systems/Systems.hpp"
#include <cstdint>
#include <memory>
#include <queue>
#include <utility>

Game::Game(ClientManager &cm, Registry &r, Sync &s, GameStartConfig config)
    : State(cm, r, s), config(config)
{}

auto Game::init_systems() -> void
{
    this->lifeRemaining = this->config.lives == 0 ? 5 : this->config.lives;
    NetworkManager &nm = this->clientManager.getNetworkManager();

    this->guiScene = std::make_unique<GameScene>(this->getGraphicalLibrary(),
                                                 *this);
    this->guiScene->init();

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
    this->registry.register_component<StraightMovingComp>();

    this->registry.add_render_system<HorizontalTiling, TextureComp>
        (animateTiling, std::ref(this->clientManager.getGui()));
    this->registry.add_render_system<HorizontalTiling, TextureComp>
        (renderHTiledTexture, std::ref(this->clientManager.getGui()));
    this->registry.add_render_system<Position, HitBox, ElementColor>
        (renderSquare, std::ref(this->getGraphicalLibrary()));
    this->registry.add_render_system<Laser, Dependence, ElementColor>
        (renderLaser, std::ref(this->getGraphicalLibrary()));
    this->registry.add_render_system<Position, PlayerId>
        (renderPlayerId, std::ref(this->getGraphicalLibrary()),
         std::ref(this->clientId));

    this->registry.add_update_system<Position, StraightMovingComp>
        (updateStraightMoving, std::ref(*this));

    this->registry.add_global_update_system
        (playerInputs, std::ref(this->clientManager.getGui()),
         std::ref(this->clientManager.getNetworkManager()),
         std::ref(*this));

    this->registry.add_global_render_system
        (renderHealth, std::ref(this->clientManager.getGui()),
         std::ref(*this));
    this->registry.add_global_render_system
        (lobbyPlayerList, std::ref(this->clientManager.getGui()),
         std::ref(*this));

    this->registry.add_global_render_system
        (renderPacketLoss, std::ref(this->clientManager.getGui()),
         std::ref(this->clientManager.getNetworkManager()));


    Entity background = this->registry.spawn_named_entity("background");
    this->registry.add_component<HorizontalTiling>(background, {2, 0, -50});
    this->registry.add_component<TextureComp>
        (background, {"background"});

    nm.addExecutor(std::make_unique<NewEnemyExecutor>(*this));
    nm.addExecutor(std::make_unique<NewBulletExecutor>(*this));
    nm.addExecutor(std::make_unique<GameOverExecutor>(*this));
    nm.addExecutor(std::make_unique<HitboxSizeUpdateExecutor>(*this));
    nm.addExecutor(std::make_unique<LaserActiveUpdateExecutor>(*this));
    nm.addExecutor(std::make_unique<PositionUpdateExecutor>(*this));
    nm.addExecutor(std::make_unique<TimeNowExecutor>(*this));
    nm.addExecutor(std::make_unique<LinkPlayersExecutor>(*this));
    nm.addExecutor(std::make_unique<DestroyEntityExecutor>(*this));
    nm.addExecutor(std::make_unique<PlayerHitExecutor>(*this));
    nm.addExecutor(std::make_unique<TextChatStringExecutorGame>(*this));
}

auto Game::init_entities() -> void {}

auto Game::newPlayer(std::string name, std::size_t player_id,
                     std::size_t laser_id)
-> void
{
    Registry &r = this->registry;
    for (auto &player : this->players)
        if (player.second.first == name)
            return;
    Entity player = r.spawn_entity();
    Entity laser = r.spawn_entity();

    this->sync.add(player.getId(), player_id);
    this->sync.add(laser.getId(), laser_id);
    r.add_component<Position>(player, {-200, -500});
    r.add_component<HitBox>(player, {20, 20});
    r.add_component<ElementColor>(player, {gl::WHITE});
    r.add_component<Health>(player, {0, 0});
    r.add_component<PlayerId>(player, {name});

    r.add_component<Dependence>(laser, {player.getId()});
    r.add_component<Laser>(laser, {true, 30});
    r.add_component<ElementColor>(laser, {gl::GREEN});
    this->players[static_cast<std::size_t>(player)] = {
        name,
        true
    };
}

auto Game::newEnemy(std::size_t enemy_id, EnemyType type) -> void
{
    Registry &r = this->registry;
    Entity enemy = r.spawn_entity();

    this->sync.add(enemy.getId(), enemy_id);
    r.add_component<Position>(enemy, {-200, -200});
    r.add_component<HitBox>(enemy, {50, 50});
    gl::Color color = gl::MAGENTA;

    if (type == EnemyType::Boss)
        color.r = 100;
    r.add_component<ElementColor>(enemy, {color});
    r.add_component<Health>(enemy, {0, 0});
}

auto Game::newBullet(std::vector<StraightMovingEntity> entities) -> void
{
    Registry &r = this->registry;
    for (auto &entity : entities) {
        Entity bullet = r.spawn_entity();

        this->sync.add(bullet.getId(), entity.id);
        r.add_component<Position>(bullet, {
            static_cast<float>(entity.pos_x),
            static_cast<float>(entity.pos_y)
        });
        r.add_component<HitBox>(bullet, {
            static_cast<float>(entity.hitbox_x),
            static_cast<float>(entity.hitbox_y)
        });
        r.add_component<ElementColor>(bullet, {gl::BLUE});
        r.add_component<StraightMovingComp>(bullet, {
            .pos_x_0 = entity.pos_x,
            .pos_y_0 = entity.pos_y,
            .vel_x = entity.vel_x,
            .vel_y = entity.vel_y,
            .ms_time = entity.ms_time
        });
    }
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

auto Game::updatePositions(std::vector<PositionData> data) -> void
{
    for (auto &pos : data)
        this->updatePosition(pos.id, pos.x, pos.y);
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

auto Game::getTime() -> uint32_t
{
    return this->startTime;
}

auto Game::setTime(uint32_t time) -> void
{
    this->startTime = time;
}

auto Game::newPlayers(std::vector<PlayerLink> data) -> void
{
    for (auto &player : data)
        this->newPlayer(player.name, player.id, player.laserId);
}

auto Game::destroyEntities(std::vector<uint16_t> ids) -> void
{
    for (auto id : ids) {
        std::optional<std::size_t> realId
            = this->sync.get_mine_from_theirs(id);
        if (!realId)
            continue;
        this->registry.kill_entity
            (this->registry.entity_from_index(*realId));
        if (this->players.contains(*realId))
            this->players[*realId].second = false;
    }
}

auto Game::updateLasers(std::vector<LaserData> data) -> void
{
    for (auto &laser : data)
        this->updateLaser(laser.id, laser.active, laser.length);
}

auto Game::getLastClientInputs() -> ClientInputs
{
    return this->lastClientInputs;
}

auto Game::setLastClientInputs(ClientInputs input) -> void
{
    this->lastClientInputs = input;
}

auto Game::getMaxHealth() -> int
{
    if (this->config.lives == 0)
        return 5;
    return this->config.lives;
}

auto Game::getCurrentHealth() -> int
{
    return this->lifeRemaining;
}

auto Game::hit() -> void
{
    this->lifeRemaining--;
}

auto Game::getPlayerList() -> std::vector<std::pair<std::string, bool>>
{
    std::vector<std::pair<std::string, bool>> vector;
    for (auto &player : this->players)
        vector.push_back(player.second);
    return vector;
}

auto Game::getChatMessage(int id) -> std::string
{
    if ((std::size_t) id >= this->messages.size())
        return "";
    return this->messages.at(id);
}

auto Game::addChatMessage(std::string message) -> void
{
    for (int i = (int) this->messages.size() - 2; i >= 0; i--)
        this->messages[i + 1] = this->messages[i];
    if (this->messages.size() > 0)
        this->messages[0] = message;
}

auto Game::sendNewMessage() -> void
{
    if (this->messageToSend.empty())
        return;
    auto packet = create_packet(TextChatStringPacket, this->messageToSend);
    this->clientManager.getNetworkManager().sendPacket(packet);
    this->messageToSend.clear();
}

auto Game::setMessage(std::string message) -> void
{
    this->messageToSend = message;
}

auto Game::getMessage() -> std::string
{
    return this->messageToSend;
}
