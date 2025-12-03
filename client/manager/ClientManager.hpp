/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** manages the client
*/

#ifndef CLIENT_MANAGER_HPP
#define CLIENT_MANAGER_HPP

#include "client/GraphicalLibInterface.hpp"

#include "ecs/regisrty/Registry.hpp"

#include <memory>

class ClientManager
{
public:
    ClientManager();
    ~ClientManager();

private:
    Registry registry;
    std::unique_ptr<GraphicalLibAPI> gui = nullptr;
};

#endif /* CLIENT_MANAGER_HPP */
