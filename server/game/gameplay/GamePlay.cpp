#include "GamePlay.hpp"

GamePlay::GamePlay(NetworkManager &nm, Registry &r)
    : _networkManager(nm), _regisrty(r), _state(GameState::waiting)
{
    _start = std::chrono::steady_clock::now();
}

void GamePlay::update()
{
    if (_state == GameState::waiting) {
        auto now = std::chrono::steady_clock::now();
        auto elapsed =
            std::chrono::duration_cast<std::chrono::milliseconds>(now - _start);
        if (elapsed.count() > 5000) {}
    }
}
