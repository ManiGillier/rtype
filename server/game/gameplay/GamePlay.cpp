#include "GamePlay.hpp"
#include "../Game.hpp"

GamePlay::GamePlay(Game &game, std::chrono::steady_clock::time_point start)
    : _game(game), _start(start), _state(GameState::waiting)
{
}

void GamePlay::update()
{
    if (_state == GameState::waiting) {
        auto now = std::chrono::steady_clock::now();
        auto elapsed =
            std::chrono::duration_cast<std::chrono::milliseconds>(now - _start);
        if (elapsed.count() > 5000) {
        }
    }
}
