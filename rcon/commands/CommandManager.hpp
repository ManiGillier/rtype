/*
** EPITECH PROJECT, 2026
** rtype [WSL: Ubuntu-24.04]
** File description:
** CommandManager
*/

#ifndef COMMANDMANAGER_HPP_
    #define COMMANDMANAGER_HPP_

    #include <vector>
    #include <rcon/commands/impl/ExitCommand.hpp>
    #include <memory>
    #include <exception>


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
                        cmd->executeCommand(cl, tokens, key);
                        break;
                    }
                    throw CommandException("Wrong argument count for " + commandName
                        + ". Usage: " + cmd->getUsage());
                }
            }
            throw CommandException("No such command " + commandName + " found.");
        }

    private:
        std::vector<std::unique_ptr<ICommand>> commands;
};

#endif /* !COMMANDMANAGER_HPP_ */
