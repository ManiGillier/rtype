/*
** EPITECH PROJECT, 2026
** rtype [WSL: Ubuntu-24.04]
** File description:
** ExitCommand
*/

#ifndef EXITCOMMAND_HPP_
    #define EXITCOMMAND_HPP_

    #include <rcon/commands/ICommand.hpp>

class ExitCommand : public ICommand {
    public:
        std::string getCommandName() const {
            return "exit";
        }

        std::string getHelp() const {
            return "Exits the program";
        }

        std::string getUsage() const {
            return "exit";
        }

        std::size_t getArgumentCount() const {
            return 0;
        }

        void executeCommand(Client &cl,
            std::vector<std::string> args, const std::string &key,
            CommandManager &cm) const {
                (void) cl;
                (void) args;
                (void) key;
                (void) cm;
                exit(0);
        }
};

#endif /* !EXITCOMMAND_HPP_ */
