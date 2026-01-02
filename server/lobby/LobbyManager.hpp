#ifndef LOBBY_MANAGER_HPP
#define LOBBY_MANAGER_HPP

#include "../player/Player.hpp"
#include "Lobby.hpp"
#include <memory>
#include <unordered_map>

class LobbyManager
{
  public:
    LobbyManager() = default;
    ~LobbyManager() = default;
    void newLobby(std::shared_ptr<Player> &player);
    void removePlayer(std::shared_ptr<Player> &player);
    bool joinLobby(const std::string &lobbyId, std::shared_ptr<Player> &player);
    void leaveLobby(std::shared_ptr<Player> &player);
    bool startGame(const std::string &lobbyId);

  private:
    std::string getRandomLobbyId(std::size_t len);
    std::unordered_map<std::string, std::unique_ptr<Lobby>> _lobbies;
};

#endif
