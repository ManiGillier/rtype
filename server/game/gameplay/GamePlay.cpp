#include "GamePlay.hpp"
#include "server/game/factories/EntityFactory.hpp"
#include <memory>

GamePlay::GamePlay(NetworkManager &nm, Registry &r, EntityFactory &factory)
    : _networkManager(nm), _regisrty(r), _factory(factory),
      _state(GameState::waiting)

{
    _start = std::chrono::steady_clock::now();
}

void GamePlay::update()
{
    if (_state == GameState::waiting) {
        auto now = std::chrono::steady_clock::now();
        auto elapsed =
            std::chrono::duration_cast<std::chrono::milliseconds>(now - _start);
        if (elapsed.count() > 5000) {
            this->spawnBoss();
            this->_state = GameState::active;
        }
    } else if (_state == GameState::active) {
        for (auto &it : _bosses)
            it->shoot();
    }
}

void GamePlay::spawnBoss()
{
    this->_bosses.push_back(
        std::make_unique<Boss>(_networkManager, _regisrty, _factory));
}
