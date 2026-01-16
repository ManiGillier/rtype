/*
** EPITECH PROJECT, 2026
** rype
** File description:
** login state
*/

#include "Login.hpp"

#include "client/network/executor/LoginExecutor.hpp"

#include <iostream>
#include <memory>

#include "gui/LoginScene.hpp"

#include <network/packets/impl/RegisterPacket.hpp>
#include <network/packets/impl/LoginPacket.hpp>

Login::Login(ClientManager &cm, Registry &r, Sync &s)
    : State(cm, r, s)
{}

auto Login::init_systems() -> void
{
    std::cout << "Init systems" << std::endl;

    this->guiScene = std::make_unique<LoginScene>(this->getGraphicalLibrary(),
                                                  *this);
    this->guiScene->init();

    this->registry.reset_update_systems();
    this->registry.reset_render_systems();

    this->clientManager.getNetworkManager().resetExecutors();

    this->clientManager.getNetworkManager()
        .addExecutor(std::make_unique<LoginResponseExecutor>(*this));
}

auto Login::init_entities() -> void
{
    std::cout << "Init entities" << std::endl;
}

auto Login::setLoginUsername(std::string username) -> void
{
    this->loginUsername = username;
}

auto Login::setLoginPassword(std::string password) -> void
{
    this->loginPassword = password;
}

auto Login::setRegisterUsername(std::string username) -> void
{
    this->registerUsername = username;
}

auto Login::setRegisterPassword(std::string password) -> void
{
    this->registerPassword = password;
}

auto Login::getLastErrorMessage() -> std::string
{
    return this->lastErrorMessage;
}

auto Login::setErrorMessage(std::string message) -> void
{
    this->lastErrorMessage = message;
}

auto Login::login() -> void
{
    std::shared_ptr<Packet> p =
        std::make_shared<LoginPacket>
            (this->loginUsername, this->loginPassword);
    this->clientManager.getNetworkManager().sendPacket(p);
}

auto Login::register_() -> void
{
    std::shared_ptr<Packet> p =
        std::make_shared<RegisterPacket>
            (this->registerUsername, this->registerPassword);
    this->clientManager.getNetworkManager().sendPacket(p);
}
