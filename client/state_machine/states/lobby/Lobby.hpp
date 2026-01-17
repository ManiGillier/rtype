/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** client lobby state
*/

#ifndef CLIENT_LOBBY_STATE_HPP
#define CLIENT_LOBBY_STATE_HPP

#include "client/state_machine/State.hpp"
#include <vector>

#include <network/packets/impl/StartGamePacket.hpp>

class Lobby : public State {
public:
    Lobby(ClientManager &cm, Registry &r, Sync &s, std::string code);

    auto init_systems() -> void;
    auto init_entities() -> void;
    auto updatePlayers(std::vector<std::string> playerList) -> void;
    auto getPlayerList() -> std::vector<std::string>;
    auto getConfig() -> GameStartConfig;
    auto setConfig(GameStartConfig config) -> void;
    auto getCode() -> std::string;
private:
    GameStartConfig config = { 1, 1 };
    std::string code;
    std::vector<std::string> playerList;
};

#endif /* CLIENT_LOBBY_STATE_HPP */
