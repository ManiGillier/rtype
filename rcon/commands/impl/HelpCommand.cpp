/*
** EPITECH PROJECT, 2026
** rtype [WSL: Ubuntu-24.04]
** File description:
** HelpCommand
*/

#include "HelpCommand.hpp"
#include <rcon/Logger.hpp>
#include <iomanip>
#include <rcon/commands/CommandManager.hpp>

void HelpCommand::executeCommand(Client &cl, std::vector<std::string> args,
                                 const std::string &key,
                                 CommandManager &cm) const
{
    const std::vector<std::unique_ptr<ICommand>> &commands = cm.getCommands();
    int maxName = 12;
    int maxHelp = 4;
    int maxUsage = 5;
    
    (void) cl;
    (void) args;
    (void) key;
    for (const auto &command : commands) {
        maxName = std::max(maxName, static_cast<int>(command->getCommandName().length()));
        maxHelp = std::max(maxHelp, static_cast<int>(command->getHelp().length()));
        maxUsage = std::max(maxUsage, static_cast<int>(command->getUsage().length()));
    }
    std::cout << std::left 
              << std::setw(maxName) << "Command Name" << " | "
              << std::setw(maxHelp) << "Help" << " | "
              << std::setw(maxUsage) << "Usage" << std::endl;
    
    std::cout << std::string(static_cast<size_t>(maxName + maxHelp + maxUsage + 6), '-') << std::endl;
    for (const auto &command : commands) {
        std::cout << std::left
                  << std::setw(maxName) << command->getCommandName() << " | "
                  << std::setw(maxHelp) << command->getHelp() << " | "
                  << std::setw(maxUsage) << command->getUsage() << std::endl;
    }
}
