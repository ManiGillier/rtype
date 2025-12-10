/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** client command
*/

#ifndef CLIENT_COMMAND_HPP
#define CLIENT_COMMAND_HPP

class Command
{
public:
    enum CommandId {
        STOP = 0,
    };
    Command(const enum CommandId id) : id(id) {}

    inline auto getId() const -> enum CommandId { return this->id; };
private:
    enum CommandId const id;
};

#endif /* CLIENT_COMMAND_HPP */
