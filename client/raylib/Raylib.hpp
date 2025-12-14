/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** raylib
*/

#ifndef RAYLIB_H_
#define RAYLIB_H_

#include "client/window/RenderWindow.hpp"
#include "client/manager/ClientManager.hpp"

#include "ecs/regisrty/Registry.hpp"

#include "client/api/IGraphicalLibrary.hpp"

class Raylib : public IGraphicalLibrary
{
public:
    Raylib(ClientManager &);
    ~Raylib();

    auto isStopped() -> bool;
    auto render(IGameState &) -> void;
private:
    ClientManager &clientManager;
    RenderWindow window;
    bool stopped = false;
};

#endif // RAYLIB_H_
