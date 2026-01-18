/*
** EPITECH PROJECT, 2026
** rype
** File description:
** lobby state
*/

#include "Lobby.hpp"

#include "client/network/executor/StartGameExecutor.hpp"
#include "client/network/executor/NewPlayerExecutor.hpp"
#include "systems/Systems.hpp"

#include <cstddef>
#include <iostream>
#include <memory>

#include <network/packets/impl/TextChatStringPacket.hpp>

#include "gui/LobbyScene.hpp"

Lobby::Lobby(ClientManager &cm, Registry &r, Sync &s, std::string code)
    : State(cm, r, s), code(code)
{}

auto Lobby::init_systems() -> void
{
    std::cout << "Init systems" << std::endl;

    this->guiScene =
        std::make_unique<LobbyScene>(this->getGraphicalLibrary(), *this);
    this->guiScene->init();

    this->registry.reset_update_systems();
    this->registry.reset_render_systems();

    this->clientManager.getNetworkManager().resetExecutors();

    this->registry.add_global_render_system
        (lobbyPlayerList, std::ref(this->clientManager.getGui()),
         std::ref(*this));

    this->clientManager.getNetworkManager()
        .addExecutor(std::make_unique<StartGameExecutor>(*this));
    this->clientManager.getNetworkManager()
        .addExecutor(std::make_unique<NewPlayerExecutor>(*this));
}

auto Lobby::init_entities() -> void
{
    std::cout << "Init entities" << std::endl;
}

auto Lobby::updatePlayers(std::vector<std::string> playerList) -> void
{
    this->playerList = playerList;
}

auto Lobby::getPlayerList() -> std::vector<std::string>
{
    return this->playerList;
}

auto Lobby::getConfig() -> GameStartConfig
{
    return this->config;
}

auto Lobby::setConfig(GameStartConfig config) -> void
{
    this->config = config;
}

auto Lobby::getCode() -> std::string
{
    return this->code;
}

auto Lobby::startGame() -> void
{
    std::shared_ptr<Packet> p = std::make_shared<StartGamePacket>(this->config);
    this->clientManager.getNetworkManager().sendPacket(p);
}

auto Lobby::getChatMessage(int id) -> std::string
{
    if ((std::size_t) id >= this->messages.size())
        return "";
    return this->messages.at(id);
}

auto Lobby::addChatMessage(std::string message) -> void
{
    for (int i = (int) this->messages.size() - 2; i >= 0; i--)
        this->messages[i + 1] = this->messages[i];
    if (this->messages.size() > 0)
        this->messages[0] = message;
}

auto Lobby::sendNewMessage() -> void
{
    if (this->messageToSend.empty())
        return;
    auto packet = create_packet(TextChatStringPacket, this->messageToSend);
    this->clientManager.getNetworkManager().sendPacket(packet);
    this->messageToSend.clear();
}

auto Lobby::setMessage(std::string message) -> void
{
    this->messageToSend = message;
}

auto Lobby::getMessage() -> std::string
{
    return this->messageToSend;
}
