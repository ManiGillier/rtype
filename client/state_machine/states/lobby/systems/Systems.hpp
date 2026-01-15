/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** lobby state systems
*/

#ifndef CLIENT_LOBBY_STATE_SYSTEMS_HPP
#define CLIENT_LOBBY_STATE_SYSTEMS_HPP

#include "ecs/regisrty/Registry.hpp"
#include "client/manager/NetworkManager.hpp"

#include "network/packets/impl/StartGamePacket.hpp"

#include <graphical_library/api/GraphicalLibrary.hpp>

#include "../Lobby.hpp"

auto gameStart([[maybe_unused]] Registry &r, gl::GraphicalLibrary &gl,
               NetworkManager &networkManager)
-> void;

auto lobbyText([[maybe_unused]] Registry &r, gl::GraphicalLibrary &gl)
-> void;

auto lobbyPlayerList([[maybe_unused]] Registry &r,
                     gl::GraphicalLibrary &gl,
                     Lobby &lobby)
-> void;

#endif /* CLIENT_LOBBY_STATE_SYSTEMS_HPP */
