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

class RTypeServer : public Server
{
  public:
    RTypeServer(int port, int ticks);
    ~RTypeServer() = default;
    std::shared_ptr<IPollable> createClient(int fd) override;
    void onClientConnect(std::shared_ptr<IPollable> client) override;
    void onClientDisconnect(std::shared_ptr<IPollable> client) override;
    void setTicks(int ticks);
    int getTicks() const;
    LobbyManager &getLobbyManager();
    void cleanFinishedGame();
    ThreadPool &getGameThreadPool();
    AccountDatabase &getAccountDatabase();

  private:
    int _ticks;
    int _nextId;
    LobbyManager _lobbyManager;
    ThreadPool _threadPool;
    AccountDatabase db;
};

#endif
