/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** client login state
*/

#ifndef CLIENT_LOGIN_STATE_HPP
#define CLIENT_LOGIN_STATE_HPP

#include "client/state_machine/State.hpp"

#include <string>

class Login : public State {
public:
    Login(ClientManager &cm, Registry &r, Sync &s);

    auto init_systems() -> void;
    auto init_entities() -> void;

    auto setLoginUsername(std::string username) -> void;
    auto setLoginPassword(std::string password) -> void;

    auto setRegisterUsername(std::string username) -> void;
    auto setRegisterPassword(std::string password) -> void;

    auto getLastErrorMessage() -> std::string;
    auto setErrorMessage(std::string message) -> void;

    auto login() -> void;
    auto register_() -> void;
private:
    std::string lastErrorMessage = "";

    std::string loginUsername = "";
    std::string loginPassword = "";

    std::string registerUsername = "";
    std::string registerPassword = "";
};

#endif /* CLIENT_LOGIN_STATE_HPP */
