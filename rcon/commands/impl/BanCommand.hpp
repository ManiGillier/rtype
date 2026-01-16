/*
** EPITECH PROJECT, 2026
** rtype [WSL: Ubuntu-24.04]
** File description:
** BanCommand
*/

#ifndef BANCOMMAND_HPP_
    #define BANCOMMAND_HPP_

    #include <rcon/commands/ICommand.hpp>
    #include <network/packets/impl/RCONRequest.hpp>

class BanCommand : public ICommand {
    public:
        std::string getCommandName() const {
            return "ban";
        }

        std::string getHelp() const {
            return "bans from the server the specified username";
        }

        std::string getUsage() const {
            return "ban <username>";
        }

        std::size_t getArgumentCount() const {
            return 1;
        }

        void executeCommand(Client &cl,
            std::vector<std::string> args, const std::string &key,
            CommandManager &cm) const {
                (void) cm;
                cl.sendPacket(create_packet(RCONRequest, RCONRequest::BAN, key, args[0]));
            }
};
#endif /* !BANCOMMAND_HPP_ */
