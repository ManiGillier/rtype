/*
** EPITECH PROJECT, 2026
** rtype [WSL: Ubuntu-24.04]
** File description:
** SetAdminCommand
*/

#ifndef SETADMINCOMMAND_HPP_
    #define SETADMINCOMMAND_HPP_

    #include <rcon/commands/ICommand.hpp>
    #include <network/packets/impl/RCONRequest.hpp>

class SetAdminCommand: public ICommand {
    public:
        std::string getCommandName() const {
            return "setadmin";
        }

        std::string getHelp() const {
            return "Flags a user as administrator of R-Type Server";
        }

        std::string getUsage() const {
            return "setadmin <username>";
        }

        std::size_t getArgumentCount() const {
            return 1;
        }

        void executeCommand(Client &cl,
            std::vector<std::string> args, const std::string &key,
            CommandManager &cm) const {
                (void) cm;

                cl.sendPacket(create_packet(RCONRequest, RCONRequest::SETADMIN, key, args[0]));
            }
};

#endif /* !SETADMINCOMMAND_HPP_ */
