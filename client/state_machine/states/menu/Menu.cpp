/*
** EPITECH PROJECT, 2026
** rype
** File description:
** menu state
*/

#include "Menu.hpp"

#include "client/network/executor/JoinedLobbyExecutor.hpp"
#include "client/network/executor/ScorePacketExecutor.hpp"
#include "gui/Scene.hpp"

#include <client/state_machine/states/settings/Settings.hpp>

#include <cstddef>
#include <iostream>
#include <memory>

#include <network/packets/impl/JoinOrCreatePublicLobby.hpp>
#include <network/packets/impl/JoinLobbyWithCodePacket.hpp>
#include <network/packets/impl/CreatePrivateLobbyPacket.hpp>
#include <network/packets/impl/ScorePacket.hpp>

Menu::Menu(ClientManager &cm, Registry &r, Sync &s)
    : State(cm, r, s)
{}

auto Menu::init_systems() -> void
{
    std::cout << "Init systems" << std::endl;

    this->guiScene = std::make_unique<MenuScene>(this->getGraphicalLibrary(),
                                                 *this);
    this->guiScene->init();


    this->registry.reset_update_systems();
    this->registry.reset_render_systems();

    this->clientManager.getNetworkManager().resetExecutors();

    this->clientManager.getNetworkManager()
        .addExecutor(std::make_unique<JoinedLobbyExecutor>(*this));
    this->clientManager.getNetworkManager()
        .addExecutor(std::make_unique<ScoreExecutor>(*this));

    auto packet = create_packet(ScorePacket, ScorePacket::REQUEST);
    this->clientManager.getNetworkManager().sendPacket(packet);
}

auto Menu::init_entities() -> void
{
    std::cout << "Init entities" << std::endl;
}

auto Menu::joinRandomLobby() -> void
{
    auto packet = create_packet(JoinOrCreatePublicLobbyPacket);
    this->clientManager.getNetworkManager().sendPacket(packet);
}

auto Menu::joinCodeLobby() -> void
{
    auto packet = create_packet(JoinLobbyWithCodePacket, this->lobbyCode);
    this->clientManager.getNetworkManager().sendPacket(packet);
}

auto Menu::createPrivateLobby() -> void
{
    auto packet = create_packet(CreatePrivateLobbyPacket);
    this->clientManager.getNetworkManager().sendPacket(packet);
}

auto Menu::setLobbyCode(std::string code) -> void
{
    this->lobbyCode = code;
}

auto Menu::getLobbyCode() -> std::string
{
    return this->lobbyCode;
}

auto Menu::settings() -> void
{
    this->change_state<Settings>();
}

auto Menu::setScores(std::vector<std::string> scores) -> void
{
    this->scores.fill("");
    int i = 0;
    for (auto &score : scores) {
        if ((std::size_t) i >= this->scores.size())
            break;
        this->scores[i] = score;
        i++;
    }
}

auto Menu::getScore(int id) -> std::string
{
    if ((std::size_t) id >= this->scores.size())
        return "";
    return this->scores.at(id);
}

auto Menu::requestScoresRefresh() -> void
{
    auto packet = create_packet(ScorePacket, ScorePacket::REQUEST);
    this->clientManager.getNetworkManager().sendPacket(packet);
}
