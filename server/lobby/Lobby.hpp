#ifndef LOBBY_HPP
#define LOBBY_HPP

#include "../player/Player.hpp"
#include "../game/Game.hpp"
#include <memory>
#include <vector>
#include <mutex>

constexpr int MIN_PLAYER = 1;
constexpr int MAX_PLAYER = 5;

class Lobby
{
  public:
    Lobby();
    ~Lobby() = default;
    bool addPlayer(std::shared_ptr<Player> &player);
    void removePlayer(std::shared_ptr<Player> &player);
    void sendNewUsrnames();
    std::mutex &getPlayersMutex();
    std::vector<std::shared_ptr<Player>> &getPlayers();
    std::size_t size() const;
    bool isFull() const;
    void startGame(GameStartConfig config, int ticks);
    bool isInGame();
    void setIsInGame(bool iig);
    Game &getGame();
    bool isPublic() const;
    void setPublic(bool isPublic);

  private:
    bool _isPublic;
    mutable std::mutex _publicMutex;
    mutable std::mutex _playersMutex;
    std::vector<std::shared_ptr<Player>> _players;
    std::mutex _GameMutex;
    bool _inGame;
    Game _game;
};

#endif
