/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** Server
*/

#ifndef RTYPES_SERVER_HPP_
#define RTYPES_SERVER_HPP_

#include "../../lobby/LobbyManager.hpp"
#include "../../thread/ThreadPool.hpp"
#include <memory>
#include <network/server/Server.hpp>
#include "../../database/AccountDatabase.hpp"


#define CONFIG_FILE "rtype.cfg"
#define TO_CHANGE "sex123123"

class RTypeConfig {
    public:
        bool createConfig();
        bool readConfig();
        bool shouldCreateConfig() const;
        const std::string &getKey() const;
    private:
        std::string key = "";
};

class RTypeServer : public Server
{
  public:
    RTypeServer(int port, int ticks);
    ~RTypeServer() = default;
    std::shared_ptr<IPollable> createClient(int fd) override;
    void onClientConnect(std::shared_ptr<IPollable> client) override;
    void onClientDisconnect(std::shared_ptr<IPollable> client) override;
    bool isConnected(const std::string &username);
    std::shared_ptr<Player> getPlayerByUsername(const std::string &username);
    void setTicks(int ticks);
    int getTicks() const;
    LobbyManager &getLobbyManager();
    void cleanFinishedGame();
    ThreadPool &getGameThreadPool();
    AccountDatabase &getAccountDatabase();
    RTypeConfig &getRTypeConfig();
  private:
    int _ticks;
    int _nextId;
    LobbyManager _lobbyManager;
    ThreadPool _threadPool;
    AccountDatabase db;
    RTypeConfig config;
};

#endif
