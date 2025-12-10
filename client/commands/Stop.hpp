/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** stop command
*/

#ifndef CLIENT_STOP_COMMAND_HPP
#define CLIENT_STOP_COMMAND_HPP

#include "Command.hpp"

class StopCommand : public Command
{
public:
    StopCommand() : Command(Command::STOP) {}
};

#endif /* CLIENT_STOP_COMMAND_HPP */
