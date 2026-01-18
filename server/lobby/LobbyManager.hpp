#ifndef LOBBY_MANAGER_HPP
#define LOBBY_MANAGER_HPP

#include "../player/Player.hpp"
#include "Lobby.hpp"
#include "network/packets/impl/StartGamePacket.hpp"
#include <memory>
#include <unordered_map>

class LobbyManager
{
  public:
    LobbyManager(int ticks);
    ~LobbyManager() = default;
    void newLobby(std::shared_ptr<Player> &player, bool publicl = false);
    void removePlayer(std::shared_ptr<Player> &player);
    bool joinLobby(const std::string &lobbyId, std::shared_ptr<Player> &player);
    bool joinPublicLobby(std::shared_ptr<Player> &player);
    void leaveLobby(std::shared_ptr<Player> &player);
    void startGame(GameStartConfig config, const std::string &lobbyId);
    void deleteLobby(const std::string& lobbyId);
    std::shared_ptr<Lobby> getLobby(const std::string& lobbyId);

  private:
    std::string getRandomLobbyId(std::size_t len);
    std::mutex _lobbiesMutex;
    std::unordered_map<std::string, std::shared_ptr<Lobby>> _lobbies;
    int _ticks;
};

#endif
