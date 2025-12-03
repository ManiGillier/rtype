/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** client manager
*/

#include "ClientManager.hpp"
#include "client/raylib/Raylib.hpp"

#include <memory>

ClientManager::ClientManager()
{
    this->gui = std::make_unique<Raylib>(this->registry);
}

ClientManager::~ClientManager() {}
