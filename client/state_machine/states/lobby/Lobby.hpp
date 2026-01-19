/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** client lobby state
*/

#ifndef CLIENT_LOBBY_STATE_HPP
#define CLIENT_LOBBY_STATE_HPP

#include "client/state_machine/State.hpp"
#include <array>
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
    auto forceSetConfig(GameStartConfig config) -> void;
    auto getCode() -> std::string;
    auto startGame() -> void;
    auto getChatMessage(int id) -> std::string;
    auto addChatMessage(std::string message) -> void;
    auto sendNewMessage() -> void;
    auto setMessage(std::string message) -> void;
    auto getMessage() -> std::string;
private:
    GameStartConfig config = { 1, 1 };
    std::string code;
    std::vector<std::string> playerList;
    std::array<std::string, 10> messages;
    std::string messageToSend = "";
};

#endif /* CLIENT_LOBBY_STATE_HPP */
