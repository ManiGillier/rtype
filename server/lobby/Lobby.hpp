#ifndef LOBBY_HPP
#define LOBBY_HPP

#include "../player/Player.hpp"
#include <memory>
#include <vector>

constexpr int MIN_PLAYER = 1;
constexpr int MAX_PLAYER = 5;

class Lobby
{
  public:
    Lobby() = default;
    ~Lobby() = default;
    bool addPlayer(std::shared_ptr<Player> &player);
    void removePlayer(std::shared_ptr<Player> &player);
    std::size_t size() const;
    bool startGame(); // start game when requested
  private:
    std::vector<std::shared_ptr<Player>> _players;
};

#endif
