/*
** EPITECH PROJECT, 2026
** rtype [WSL: Ubuntu-24.04]
** File description:
** ListCommand
*/

#ifndef LISTCOMMAND_HPP_
    #define LISTCOMMAND_HPP_

    #include <rcon/commands/ICommand.hpp>
    #include <network/packets/impl/RCONRequest.hpp>

class ListCommand : public ICommand {
    public:
        std::string getCommandName() const {
            return "list";
        }

        std::string getHelp() const {
            return "Get a list of all players";
        }

        std::string getUsage() const {
            return "list";
        }

        std::size_t getArgumentCount() const {
            return 0;
        }

        void executeCommand(Client &cl,
            std::vector<std::string> args, const std::string &key,
            CommandManager &cm) const {
                (void) args;
                (void) cm;

                cl.sendPacket(create_packet(RCONRequest, RCONRequest::LIST, key));
            }
};

#endif /* !LISTCOMMAND_HPP_ */
