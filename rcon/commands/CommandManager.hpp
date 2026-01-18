/*
** EPITECH PROJECT, 2026
** rtype [WSL: Ubuntu-24.04]
** File description:
** CommandManager
*/

#ifndef COMMANDMANAGER_HPP_
    #define COMMANDMANAGER_HPP_

    #include <vector>
    #include <memory>
    #include <exception>

    #include <rcon/commands/impl/ExitCommand.hpp>
    #include <rcon/commands/impl/HelpCommand.hpp>
    #include <rcon/commands/impl/ListCommand.hpp>
    #include <rcon/commands/impl/KickCommand.hpp>
    #include <rcon/commands/impl/BanCommand.hpp>
    #include <rcon/commands/impl/UnbanCommand.hpp>
    #include <rcon/commands/impl/BanlistCommand.hpp>
    #include <rcon/commands/impl/SetAdminCommand.hpp>

class CommandManager {
    public:
        class CommandException : public std::exception {
            public:
                CommandException(const std::string &error) {
                    this->exception = error;
                }

                const char *what() const noexcept override {
                    return exception.c_str();
                }
            private:
                std::string exception;
        };

        CommandManager() {
            commands.push_back(std::make_unique<ExitCommand>());
            commands.push_back(std::make_unique<HelpCommand>());
            commands.push_back(std::make_unique<ListCommand>());
            commands.push_back(std::make_unique<KickCommand>());
            commands.push_back(std::make_unique<BanCommand>());
            commands.push_back(std::make_unique<UnbanCommand>());
            commands.push_back(std::make_unique<BanlistCommand>());
            commands.push_back(std::make_unique<SetAdminCommand>());
        }

        void execute(Client &cl, const std::string &line,
            const std::string &key) {
            std::vector<std::string> tokens;
            std::istringstream stream(line);
            std::string token;
            
            while (stream >> token)
                tokens.push_back(token);
            if (tokens.empty())
                return;
            std::string commandName = tokens[0];
            tokens.erase(tokens.begin());
            for (std::unique_ptr<ICommand> &cmd : this->commands) {
                if (cmd->getCommandName() == commandName) {
                    if (cmd->getArgumentCount() == tokens.size()) {
                        cmd->executeCommand(cl, tokens, key, *this);
                        return;
                    }
                    throw CommandException("Wrong argument count for " + commandName
                        + ". Usage: " + cmd->getUsage());
                }
            }
            throw CommandException("No such command " + commandName + " found.");
        }

        const std::vector<std::unique_ptr<ICommand>> &getCommands() const {
            return this->commands;
        }

    private:
        std::vector<std::unique_ptr<ICommand>> commands;
};

#endif /* !COMMANDMANAGER_HPP_ */
