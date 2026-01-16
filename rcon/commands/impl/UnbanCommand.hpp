/*
** EPITECH PROJECT, 2026
** rtype [WSL: Ubuntu-24.04]
** File description:
** UnbanCommand
*/

#ifndef UNBANCOMMAND_HPP_
    #define UNBANCOMMAND_HPP_

    #include <rcon/commands/ICommand.hpp>
    #include <network/packets/impl/RCONRequest.hpp>

class UnbanCommand : public ICommand {
    public:
        std::string getCommandName() const {
            return "unban";
        }

        std::string getHelp() const {
            return "unbans from the server the specified username";
        }

        std::string getUsage() const {
            return "unban <username>";
        }

        std::size_t getArgumentCount() const {
            return 1;
        }

        void executeCommand(Client &cl,
            std::vector<std::string> args, const std::string &key,
            CommandManager &cm) const {
                (void) cm;
                cl.sendPacket(create_packet(RCONRequest, RCONRequest::UNBAN, key, args[0]));
            }
};
#endif /* !UNBANCOMMAND_HPP_ */
