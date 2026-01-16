/*
** EPITECH PROJECT, 2026
** rtype [WSL: Ubuntu-24.04]
** File description:
** ICommand
*/

#ifndef ICOMMAND_HPP_
    #define ICOMMAND_HPP_

    #include <string>
    #include <vector>
    #include <network/client/Client.hpp>

class CommandManager;

class ICommand {
    public:
        virtual std::string getCommandName() const = 0;
        virtual std::size_t getArgumentCount() const = 0;
        virtual void executeCommand(Client &cl,
            std::vector<std::string> args,
            const std::string &key,
            CommandManager &cm) const = 0;
        virtual std::string getHelp() const = 0;
        virtual std::string getUsage() const = 0;
};

#endif /* !ICOMMAND_HPP_ */
