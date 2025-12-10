#include "game/Game.hpp"
#include "player/Player.hpp"
#include <memory>

int main()
{
    std::unique_ptr<Player> p1 = std::make_unique<Player>(0);
    std::unique_ptr<Player> p2 = std::make_unique<Player>(1);

    Game game;

    game.addPlayer(p1);
    game.addPlayer(p2);

    game.start();
    for (int i = 0; i < 1; i++)
        game.update();
    return 0;
}
