/*
** EPITECH PROJECT, 2026
** rtype [WSL: Ubuntu-24.04]
** File description:
** KickCommand
*/

#ifndef KICKCOMMAND_HPP_
    #define KICKCOMMAND_HPP_

    #include <rcon/commands/ICommand.hpp>
    #include <network/packets/impl/RCONRequest.hpp>

class KickCommand : public ICommand {
    public:
        std::string getCommandName() const {
            return "kick";
        }

        std::string getHelp() const {
            return "Kicks from the server the specified username";
        }

        std::string getUsage() const {
            return "kick <username>";
        }

        std::size_t getArgumentCount() const {
            return 1;
        }

        void executeCommand(Client &cl,
            std::vector<std::string> args, const std::string &key,
            CommandManager &cm) const {
                (void) cm;
                cl.sendPacket(create_packet(RCONRequest, RCONRequest::KICK, key, args[0]));
            }
};
#endif /* !KICKCOMMAND_HPP_ */
