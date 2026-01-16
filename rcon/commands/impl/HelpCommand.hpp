/*
** EPITECH PROJECT, 2026
** rtype [WSL: Ubuntu-24.04]
** File description:
** HelpCommand
*/

#ifndef HELPCOMMAND_HPP_
    #define HELPCOMMAND_HPP_

    #include <rcon/commands/ICommand.hpp>

class HelpCommand : public ICommand {
    public:
        std::string getCommandName() const {
            return "help";
        }

        std::string getHelp() const {
            return "Displays the help menu";
        }

        std::string getUsage() const {
            return "help";
        }

        std::size_t getArgumentCount() const {
            return 0;
        }

        void executeCommand(Client &cl,
            std::vector<std::string> args, const std::string &key,
            CommandManager &cm) const;
};
#endif /* !HELPCOMMAND_HPP_ */
